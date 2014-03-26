///
/// \file     sql_toolbox.cpp
/// \brief    Toolbox of functions for sql persistance
/// \author   Frederic Manisse
/// \version  1.0
///
/// Toolbox of functions for sql persistance
///
#include <laurena/sql/sql_toolbox.hpp>
#include <laurena/sql/sql_annotations.hpp>

using namespace laurena;
using namespace sql;

const field* sql_toolbox::primaryKeyField(const descriptor& desc)
{
const sql_column* col;

	const fields& fs = desc.get_fields();
	for (const std::unique_ptr<field>& pf : fs)
	{
		const field* f = pf.get();
		if (! (col = dynamic_cast<const sql_column*>(f->annotations().get(sql_column::ANNOTATION_NAME))))			
			continue;

		if (col->isPrimaryKey())
			return f;
	}

	const polymorphic_feature* pcf = dynamic_cast<const polymorphic_feature*>(desc.feature(Feature::POLYMORPHIC));
	if (!pcf)
		return nullptr;

	if (!pcf->hasParent())
		return nullptr;

	return sql_toolbox::primaryKeyField(pcf->parent());
}
//End of file