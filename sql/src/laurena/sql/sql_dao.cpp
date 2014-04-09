///
/// \file     sql_dao.cpp
/// \brief    DAO base class and templated class
/// \author   Frederic Manisse
/// \version  1.0
///
/// Annotations for sql persistance
///
#include <laurena/sql/sql_dao.hpp>
#include <laurena/sql/sql_annotations.hpp>
#include <laurena/sql/sql_toolbox.hpp>
#include <laurena/sql/sql_error.hpp>

using namespace laurena;
using namespace sql;

sql_dao::sql_dao(const descriptor& desc, sql_database& db) : dao (desc), _db(db)
{ }

sql_dao::~sql_dao()
{ }

any& sql_dao::read    (const any& primaryKey, any& destination)
{
    return destination;
}

any& sql_dao::create  (any& object)
{
    return object;
}

any& sql_dao::update  (any& object)
{
    return object;
}

void sql_dao::erase   (any& object)
{
}

void sql_dao::erase   (const any& primaryKey)
{

}

bool sql_dao::exist   (const any& primaryKey)
{
    return false;
}

    std::string sql_dao::create_table_query()
    {
        return "";
    }
    /*
std::string sql_dao::create_table_query(const descriptor& desc, const sql_tablename& table)
{
    const fields& fs = pdesc->get_fields();
	for (const std::unique_ptr<field>& pf : fs)
	{
	    const field& f = *pf;
}
*/
std::string sql_dao::insert_query(const any& object)
{
std::ostringstream sFields, sValues, sQuery;
const sql_tablename* original_tablename = dynamic_cast<const sql_tablename*>(this->_descriptor.annotations().get(sql_tablename::ANNOTATION_NAME));
const sql_column* col;
const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(this->_descriptor.feature(Feature::POLYMORPHIC));
any v;
const descriptor* pdesc = &this->_descriptor;
bool first = true;

	if (!original_tablename)
		sql_error::noTablename(this->_descriptor);

	const sql_tablename* current = original_tablename;
	while (current->name() == original_tablename->name())
	{
		if (pdesc->has(descriptor::Flags::FIELDS))
		{
			const fields& fs = pdesc->get_fields();
			for (const std::unique_ptr<field>& pf : fs)
			{
				const field& f = *pf;
				if (! (col = dynamic_cast<const sql_column*>(f.annotations().get(sql_column::ANNOTATION_NAME))))			
					continue;

				if (first)
					first = false;
				else
				{
					sFields << ", ";
					sValues << ", ";
				}
				sFields << col->column();
				f.get(object, v);
				sValues << "'" << v.tos() << "'";
			}
		}

		if (!pcf)
			break;
		if (!pcf->hasParent())
			break;

		pdesc = &pcf->parent();
		current = dynamic_cast<const sql_tablename*>(pdesc->annotations().get(sql_tablename::ANNOTATION_NAME));
		pcf = dynamic_cast<const polymorphic_feature*>(pdesc->feature(Feature::POLYMORPHIC));

	}

	sQuery << "INSERT INTO " << original_tablename->tablename() << " (" << sFields.str() << ") VALUES (" << sValues.str() << ");" ;
	return sQuery.str();

}

std::string sql_dao::select_by_primary_key_query(any& primary_key)
{
std::ostringstream sQuery;
const sql_tablename* original_tablename = dynamic_cast<const sql_tablename*>(this->_descriptor.annotations().get(sql_tablename::ANNOTATION_NAME));
const sql_column* col;
const sql_column* primary_key_col = nullptr;
const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(this->_descriptor.feature(Feature::POLYMORPHIC));
any v;
const descriptor* pdesc = &this->_descriptor;

	if (!original_tablename)
		sql_error::noTablename(this->_descriptor);

	sQuery << "SELECT ";

	const sql_tablename* current = original_tablename;
	bool first = true;
	while (current->name() == original_tablename->name())
	{
		if (pdesc->has(descriptor::Flags::FIELDS))
		{
			const fields& fs = pdesc->get_fields();
			for (const std::unique_ptr<field>& pf : fs)
			{
				const field& f = *pf;
				if (! (col = dynamic_cast<const sql_column*>(f.annotations().get(sql_column::ANNOTATION_NAME))))			
					continue;

				if (col->isPrimaryKey())
				{
					if (primary_key_col)
						sql_error::twoPrimaryKeys(this->_descriptor);
					primary_key_col = col;
				}

				if (first)
					first = false;
				else
					sQuery << ", ";

				sQuery << col->column();
			}
		}

		if (!pcf)
			break;
		if (!pcf->hasParent())
			break;

		pdesc = &pcf->parent();
		current = dynamic_cast<const sql_tablename*>(pdesc->annotations().get(sql_tablename::ANNOTATION_NAME));
		pcf = dynamic_cast<const polymorphic_feature*>(pdesc->feature(Feature::POLYMORPHIC));
	}

	if (!primary_key_col)
		sql_error::noPrimaryKey(this->_descriptor);

	sQuery << " FROM " << original_tablename->tablename() << " WHERE " << primary_key_col->column() << "='" << primary_key.tos() << "';";
	return sQuery.str();
}

std::string sql_dao::delete_by_primary_key_query(any& primary_key)
{
	const sql_tablename* original_tablename = dynamic_cast<const sql_tablename*>(this->_descriptor.annotations().get(sql_tablename::ANNOTATION_NAME));
	if (! original_tablename)
	{

	}
	const field* pkField = sql_toolbox::primaryKeyField(this->_descriptor);
	if (!pkField)
		sql_error::noPrimaryKey(this->_descriptor);

	const sql_column* col = dynamic_cast<const sql_column*>(pkField->annotations().get(sql_column::ANNOTATION_NAME));
	assert(col); 

	std::ostringstream sQuery;
	sQuery << "DELETE FROM " << original_tablename->tablename() << " WHERE " << col->column() << "='" << primary_key.tos() << "';" ;


	return sQuery.str();


}
//End of file
