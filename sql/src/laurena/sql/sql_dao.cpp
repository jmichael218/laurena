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

using namespace laurena;
using namespace sql;

std::string dao::generateInsertStatement(const descriptor& desc, const any& object)
{
std::ostringstream sFields, sValues, sQuery;
const sql_tablename* original_tablename = dynamic_cast<const sql_tablename*>(desc.annotations().get("sql_tablename"));
const sql_column* col;
const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(desc.feature(Feature::POLYMORPHIC));
any v;
const descriptor* pdesc = &desc;

	if (!original_tablename)
	{
		std::string message ( desc.name());
		message += " doesn't have a 'sql_tablename' annotation";
		throw LAURENA_NULL_POINTER_EXCEPTION(message);
	}

	const sql_tablename* current = original_tablename;
	bool first = true;
	while (current->name() == original_tablename->name())
	{
		if (pdesc->has(descriptor::Flags::FIELDS))
		{
			const fields& fs = pdesc->getFields();
			for (const std::unique_ptr<field>& pf : fs)
			{
				const field& f = *pf;
				if (! (col = dynamic_cast<const sql_column*>(f.annotations().get("sql_column"))))			
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
		current = dynamic_cast<const sql_tablename*>(pdesc->annotations().get("sql_tablename"));
		pcf = dynamic_cast<const polymorphic_feature*>(pdesc->feature(Feature::POLYMORPHIC));

	}

	sQuery << "INSERT INTO " << original_tablename->tablename() << " (" << sFields.str() << ") VALUES (" << sValues.str() << ");" ;
	return sQuery.str();

}

std::string dao::generateSelectByPrimaryKey(const descriptor& desc, any& primary_key)
{
std::ostringstream sQuery;
const sql_tablename* original_tablename = dynamic_cast<const sql_tablename*>(desc.annotations().get("sql_tablename"));
const sql_column* col;
const sql_column* primary_key_col = nullptr;
const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(desc.feature(Feature::POLYMORPHIC));
any v;
const descriptor* pdesc = &desc;

	if (!original_tablename)
	{
		std::string message ( desc.name());
		message += " doesn't have a 'sql_tablename' annotation";
		throw LAURENA_NULL_POINTER_EXCEPTION(message);
	}

	sQuery << "SELECT ";

	const sql_tablename* current = original_tablename;
	bool first = true;
	while (current->name() == original_tablename->name())
	{
		if (pdesc->has(descriptor::Flags::FIELDS))
		{
			const fields& fs = pdesc->getFields();
			for (const std::unique_ptr<field>& pf : fs)
			{
				const field& f = *pf;
				if (! (col = dynamic_cast<const sql_column*>(f.annotations().get("sql_column"))))			
					continue;

				if (col->isPrimaryKey())
				{
					if (primary_key_col)
					{
						std::string message ("class ");
						message += pdesc->name();
						message += " has two columns flagged primary key";
						throw LAURENA_EXCEPTION(message);
					}
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
		current = dynamic_cast<const sql_tablename*>(pdesc->annotations().get("sql_tablename"));
		pcf = dynamic_cast<const polymorphic_feature*>(pdesc->feature(Feature::POLYMORPHIC));
	}

	if (!primary_key_col)
	{
		std::string message ("class ");
		message += pdesc->name();
		message += " has no defined primary key sql column";
		throw LAURENA_EXCEPTION(message);
	}

	sQuery << " FROM " << original_tablename->tablename() << " WHERE " << primary_key_col->column() << "='" << primary_key.tos() << "';";
	return sQuery.str();
}
//End of file
