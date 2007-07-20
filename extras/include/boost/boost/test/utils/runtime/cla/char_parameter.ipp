//  (C) Copyright Gennadiy Rozental 2005.
//  Use, modification, and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile: char_parameter.ipp,v $
//
//  Version     : $Revision: 1.1.1.1 $
//
//  Description : implements model of parameter with single char name
// ***************************************************************************

#ifndef BOOST_RT_CLA_CHAR_PARAMETER_IPP_062904GER
#define BOOST_RT_CLA_CHAR_PARAMETER_IPP_062904GER

// Boost.Runtime.Parameter
#include <boost/test/utils/runtime/config.hpp>

#include <boost/test/utils/runtime/cla/char_parameter.hpp>

namespace boost {

namespace BOOST_RT_PARAM_NAMESPACE {

namespace cla {

// ************************************************************************** //
// **************               char_name_policy               ************** //
// ************************************************************************** //

BOOST_RT_PARAM_INLINE 
char_name_policy::char_name_policy()
: basic_naming_policy( rtti::type_id<char_name_policy>() )
{
    assign_op( m_prefix, BOOST_RT_PARAM_CSTRING_LITERAL( "-" ), 0 );
}

//____________________________________________________________________________//

BOOST_RT_PARAM_INLINE bool
char_name_policy::conflict_with( identification_policy const& id ) const
{
    return id.p_type_id == p_type_id && 
           m_name == static_cast<char_name_policy const&>( id ).m_name;
}

//____________________________________________________________________________//

} // namespace cla

} // namespace BOOST_RT_PARAM_NAMESPACE

} // namespace boost

// ************************************************************************** //
//   Revision History:
//
//   $Log: char_parameter.ipp,v $
//   Revision 1.1.1.1  2007/06/12 15:03:25  duncan
//   Import of Boost 1.33.1
//
//   Revision 1.2  2005/04/12 07:01:36  rogeeff
//   exclude polymorphic_downcast
//
//   Revision 1.1  2005/04/12 06:42:43  rogeeff
//   Runtime.Param library initial commit
//
// ************************************************************************** //

#endif // BOOST_RT_CLA_CHAR_PARAMETER_IPP_062904GER