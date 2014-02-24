// Copyright (C) 2005-2008 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef OUTPUT_CONTENT_LEVELS_LEVEL_XML_H
#define OUTPUT_CONTENT_LEVELS_LEVEL_XML_H

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3020000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

#include <xsd/cxx/xml/dom/serialization-header.hxx>
#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/tree/serialization/byte.hxx>
#include <xsd/cxx/tree/serialization/unsigned-byte.hxx>
#include <xsd/cxx/tree/serialization/short.hxx>
#include <xsd/cxx/tree/serialization/unsigned-short.hxx>
#include <xsd/cxx/tree/serialization/int.hxx>
#include <xsd/cxx/tree/serialization/unsigned-int.hxx>
#include <xsd/cxx/tree/serialization/long.hxx>
#include <xsd/cxx/tree/serialization/unsigned-long.hxx>
#include <xsd/cxx/tree/serialization/boolean.hxx>
#include <xsd/cxx/tree/serialization/float.hxx>
#include <xsd/cxx/tree/serialization/double.hxx>
#include <xsd/cxx/tree/serialization/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type Type;
  typedef ::xsd::cxx::tree::simple_type< Type > SimpleType;
  typedef ::xsd::cxx::tree::type Container;

  // 8-bit
  //
  typedef signed char Byte;
  typedef unsigned char UnsignedByte;

  // 16-bit
  //
  typedef short Short;
  typedef unsigned short UnsignedShort;

  // 32-bit
  //
  typedef int Int;
  typedef unsigned int UnsignedInt;

  // 64-bit
  //
  typedef long long Long;
  typedef unsigned long long UnsignedLong;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long Integer;
  typedef long long NonPositiveInteger;
  typedef unsigned long long NonNegativeInteger;
  typedef unsigned long long PositiveInteger;
  typedef long long NegativeInteger;

  // Boolean.
  //
  typedef bool Boolean;

  // Floating-point types.
  //
  typedef float Float;
  typedef double Double;
  typedef double Decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, SimpleType > String;
  typedef ::xsd::cxx::tree::normalized_string< char, String > NormalizedString;
  typedef ::xsd::cxx::tree::token< char, NormalizedString > Token;
  typedef ::xsd::cxx::tree::name< char, Token > Name;
  typedef ::xsd::cxx::tree::nmtoken< char, Token > Nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, SimpleType, Nmtoken > Nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, Name > Ncname;
  typedef ::xsd::cxx::tree::language< char, Token > Language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, Ncname > Id;
  typedef ::xsd::cxx::tree::idref< Type, char, Ncname > Idref;
  typedef ::xsd::cxx::tree::idrefs< char, SimpleType, Idref > Idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, SimpleType > Uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, SimpleType, Uri, Ncname > Qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > Buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, SimpleType > Base64Binary;
  typedef ::xsd::cxx::tree::hex_binary< char, SimpleType > HexBinary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone TimeZone;
  typedef ::xsd::cxx::tree::date< char, SimpleType > Date;
  typedef ::xsd::cxx::tree::date_time< char, SimpleType > DateTime;
  typedef ::xsd::cxx::tree::duration< char, SimpleType > Duration;
  typedef ::xsd::cxx::tree::gday< char, SimpleType > Gday;
  typedef ::xsd::cxx::tree::gmonth< char, SimpleType > Gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, SimpleType > GmonthDay;
  typedef ::xsd::cxx::tree::gyear< char, SimpleType > Gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, SimpleType > GyearMonth;
  typedef ::xsd::cxx::tree::time< char, SimpleType > Time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, Ncname > Entity;
  typedef ::xsd::cxx::tree::entities< char, SimpleType, Entity > Entities;

  // Namespace information and list stream. Used in
  // serialization functions.
  //
  typedef ::xsd::cxx::xml::dom::namespace_info < char > NamespaceInfo;
  typedef ::xsd::cxx::xml::dom::namespace_infomap < char > NamespaceInfomap;
  typedef ::xsd::cxx::tree::list_stream < char > ListStream;
  typedef ::xsd::cxx::tree::as_double < Double > AsDouble;
  typedef ::xsd::cxx::tree::as_decimal < Decimal > AsDecimal;
  typedef ::xsd::cxx::tree::facet Facet;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags Flags;
  typedef ::xsd::cxx::tree::properties< char > Properties;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > Exception;
  typedef ::xsd::cxx::tree::bounds< char > Bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > DuplicateId;
  typedef ::xsd::cxx::tree::parsing< char > Parsing;
  typedef ::xsd::cxx::tree::expected_element< char > ExpectedElement;
  typedef ::xsd::cxx::tree::unexpected_element< char > UnexpectedElement;
  typedef ::xsd::cxx::tree::expected_attribute< char > ExpectedAttribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > UnexpectedEnumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > ExpectedTextContent;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > NoPrefixMapping;
  typedef ::xsd::cxx::tree::serialization< char > Serialization;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity Severity;
  typedef ::xsd::cxx::tree::error< char > Error;
  typedef ::xsd::cxx::tree::diagnostics< char > Diagnostics;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > ErrorHandler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::auto_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY_IN___XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY_IN___XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const treeNodeKey = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
namespace AT
{
  namespace XML
  {
    class VectorType;
    class VelocityType;
    class RectangleType;
    class LauncherType;
    class LaunchersType;
    class ReceiverType;
    class WallsType;
    class FlowType;
    class LevelType;
  }
}


#include <memory>    // std::auto_ptr
#include <algorithm> // std::binary_search

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

namespace AT
{
  namespace XML
  {
    class VectorType: public ::xml_schema::Type
    {
      public:
      // x
      // 
      typedef ::xml_schema::Int XType;
      typedef ::xsd::cxx::tree::traits< XType, char > XTraits;

      const XType&
      x () const;

      XType&
      x ();

      void
      x (const XType& x);

      // y
      // 
      typedef ::xml_schema::Int YType;
      typedef ::xsd::cxx::tree::traits< YType, char > YTraits;

      const YType&
      y () const;

      YType&
      y ();

      void
      y (const YType& x);

      // Constructors.
      //
      VectorType (const XType&,
                  const YType&);

      VectorType (const ::xercesc::DOMElement& e,
                  ::xml_schema::Flags f = 0,
                  ::xml_schema::Container* c = 0);

      VectorType (const VectorType& x,
                  ::xml_schema::Flags f = 0,
                  ::xml_schema::Container* c = 0);

      virtual VectorType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~VectorType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      ::xsd::cxx::tree::one< XType > x_;
      ::xsd::cxx::tree::one< YType > y_;
    };

    class VelocityType: public ::xml_schema::Type
    {
      public:
      // position
      // 
      typedef ::AT::XML::VectorType PositionType;
      typedef ::xsd::cxx::tree::traits< PositionType, char > PositionTraits;

      const PositionType&
      position () const;

      PositionType&
      position ();

      void
      position (const PositionType& x);

      void
      position (::std::auto_ptr< PositionType > p);

      // direction
      // 
      typedef ::xml_schema::Float DirectionType;
      typedef ::xsd::cxx::tree::traits< DirectionType, char > DirectionTraits;

      const DirectionType&
      direction () const;

      DirectionType&
      direction ();

      void
      direction (const DirectionType& x);

      static const DirectionType&
      directionDefaultValue ();

      // strength
      // 
      typedef ::xml_schema::Float StrengthType;
      typedef ::xsd::cxx::tree::traits< StrengthType, char > StrengthTraits;

      const StrengthType&
      strength () const;

      StrengthType&
      strength ();

      void
      strength (const StrengthType& x);

      static const StrengthType&
      strengthDefaultValue ();

      // Constructors.
      //
      VelocityType (const PositionType&,
                    const DirectionType&,
                    const StrengthType&);

      VelocityType (::std::auto_ptr< PositionType >&,
                    const DirectionType&,
                    const StrengthType&);

      VelocityType (const ::xercesc::DOMElement& e,
                    ::xml_schema::Flags f = 0,
                    ::xml_schema::Container* c = 0);

      VelocityType (const VelocityType& x,
                    ::xml_schema::Flags f = 0,
                    ::xml_schema::Container* c = 0);

      virtual VelocityType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~VelocityType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      ::xsd::cxx::tree::one< PositionType > position_;
      ::xsd::cxx::tree::one< DirectionType > direction_;
      static const DirectionType direction_default_value_;
      ::xsd::cxx::tree::one< StrengthType > strength_;
      static const StrengthType strength_default_value_;
    };

    class RectangleType: public ::xml_schema::Type
    {
      public:
      // x
      // 
      typedef ::xml_schema::Int XType;
      typedef ::xsd::cxx::tree::traits< XType, char > XTraits;

      const XType&
      x () const;

      XType&
      x ();

      void
      x (const XType& x);

      // y
      // 
      typedef ::xml_schema::Int YType;
      typedef ::xsd::cxx::tree::traits< YType, char > YTraits;

      const YType&
      y () const;

      YType&
      y ();

      void
      y (const YType& x);

      // width
      // 
      typedef ::xml_schema::UnsignedInt WidthType;
      typedef ::xsd::cxx::tree::traits< WidthType, char > WidthTraits;

      const WidthType&
      width () const;

      WidthType&
      width ();

      void
      width (const WidthType& x);

      // height
      // 
      typedef ::xml_schema::UnsignedInt HeightType;
      typedef ::xsd::cxx::tree::traits< HeightType, char > HeightTraits;

      const HeightType&
      height () const;

      HeightType&
      height ();

      void
      height (const HeightType& x);

      // Constructors.
      //
      RectangleType (const XType&,
                     const YType&,
                     const WidthType&,
                     const HeightType&);

      RectangleType (const ::xercesc::DOMElement& e,
                     ::xml_schema::Flags f = 0,
                     ::xml_schema::Container* c = 0);

      RectangleType (const RectangleType& x,
                     ::xml_schema::Flags f = 0,
                     ::xml_schema::Container* c = 0);

      virtual RectangleType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~RectangleType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      ::xsd::cxx::tree::one< XType > x_;
      ::xsd::cxx::tree::one< YType > y_;
      ::xsd::cxx::tree::one< WidthType > width_;
      ::xsd::cxx::tree::one< HeightType > height_;
    };

    class LauncherType: public ::xml_schema::Type
    {
      public:
      // initialParticles
      // 
      typedef ::xml_schema::UnsignedShort InitialParticlesType;
      typedef ::xsd::cxx::tree::traits< InitialParticlesType, char > InitialParticlesTraits;

      const InitialParticlesType&
      initialParticles () const;

      InitialParticlesType&
      initialParticles ();

      void
      initialParticles (const InitialParticlesType& x);

      static const InitialParticlesType&
      initialParticlesDefaultValue ();

      // position
      // 
      typedef ::AT::XML::VectorType PositionType;
      typedef ::xsd::cxx::tree::traits< PositionType, char > PositionTraits;

      const PositionType&
      position () const;

      PositionType&
      position ();

      void
      position (const PositionType& x);

      void
      position (::std::auto_ptr< PositionType > p);

      // speed
      // 
      typedef ::xml_schema::Float SpeedType;
      typedef ::xsd::cxx::tree::traits< SpeedType, char > SpeedTraits;

      const SpeedType&
      speed () const;

      SpeedType&
      speed ();

      void
      speed (const SpeedType& x);

      static const SpeedType&
      speedDefaultValue ();

      // direction
      // 
      typedef ::xml_schema::Float DirectionType;
      typedef ::xsd::cxx::tree::traits< DirectionType, char > DirectionTraits;

      const DirectionType&
      direction () const;

      DirectionType&
      direction ();

      void
      direction (const DirectionType& x);

      static const DirectionType&
      directionDefaultValue ();

      // radius
      // 
      typedef ::xml_schema::UnsignedInt RadiusType;
      typedef ::xsd::cxx::tree::traits< RadiusType, char > RadiusTraits;

      const RadiusType&
      radius () const;

      RadiusType&
      radius ();

      void
      radius (const RadiusType& x);

      static const RadiusType&
      radiusDefaultValue ();

      // Constructors.
      //
      LauncherType (const InitialParticlesType&,
                    const PositionType&,
                    const SpeedType&,
                    const DirectionType&,
                    const RadiusType&);

      LauncherType (const InitialParticlesType&,
                    ::std::auto_ptr< PositionType >&,
                    const SpeedType&,
                    const DirectionType&,
                    const RadiusType&);

      LauncherType (const ::xercesc::DOMElement& e,
                    ::xml_schema::Flags f = 0,
                    ::xml_schema::Container* c = 0);

      LauncherType (const LauncherType& x,
                    ::xml_schema::Flags f = 0,
                    ::xml_schema::Container* c = 0);

      virtual LauncherType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~LauncherType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      ::xsd::cxx::tree::one< InitialParticlesType > initialParticles_;
      static const InitialParticlesType initialParticles_default_value_;
      ::xsd::cxx::tree::one< PositionType > position_;
      ::xsd::cxx::tree::one< SpeedType > speed_;
      static const SpeedType speed_default_value_;
      ::xsd::cxx::tree::one< DirectionType > direction_;
      static const DirectionType direction_default_value_;
      ::xsd::cxx::tree::one< RadiusType > radius_;
      static const RadiusType radius_default_value_;
    };

    class LaunchersType: public ::xml_schema::Type
    {
      public:
      // launcher
      // 
      typedef ::AT::XML::LauncherType LauncherType;
      typedef ::xsd::cxx::tree::sequence< LauncherType > LauncherSequence;
      typedef LauncherSequence::iterator LauncherIterator;
      typedef LauncherSequence::const_iterator LauncherConstIterator;
      typedef ::xsd::cxx::tree::traits< LauncherType, char > LauncherTraits;

      const LauncherSequence&
      launcher () const;

      LauncherSequence&
      launcher ();

      void
      launcher (const LauncherSequence& s);

      // Constructors.
      //
      LaunchersType ();

      LaunchersType (const ::xercesc::DOMElement& e,
                     ::xml_schema::Flags f = 0,
                     ::xml_schema::Container* c = 0);

      LaunchersType (const LaunchersType& x,
                     ::xml_schema::Flags f = 0,
                     ::xml_schema::Container* c = 0);

      virtual LaunchersType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~LaunchersType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      LauncherSequence launcher_;
    };

    class ReceiverType: public ::xml_schema::Type
    {
      public:
      // position
      // 
      typedef ::AT::XML::VectorType PositionType;
      typedef ::xsd::cxx::tree::traits< PositionType, char > PositionTraits;

      const PositionType&
      position () const;

      PositionType&
      position ();

      void
      position (const PositionType& x);

      void
      position (::std::auto_ptr< PositionType > p);

      // radius
      // 
      typedef ::xml_schema::UnsignedInt RadiusType;
      typedef ::xsd::cxx::tree::traits< RadiusType, char > RadiusTraits;

      const RadiusType&
      radius () const;

      RadiusType&
      radius ();

      void
      radius (const RadiusType& x);

      static const RadiusType&
      radiusDefaultValue ();

      // Constructors.
      //
      ReceiverType (const PositionType&,
                    const RadiusType&);

      ReceiverType (::std::auto_ptr< PositionType >&,
                    const RadiusType&);

      ReceiverType (const ::xercesc::DOMElement& e,
                    ::xml_schema::Flags f = 0,
                    ::xml_schema::Container* c = 0);

      ReceiverType (const ReceiverType& x,
                    ::xml_schema::Flags f = 0,
                    ::xml_schema::Container* c = 0);

      virtual ReceiverType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~ReceiverType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      ::xsd::cxx::tree::one< PositionType > position_;
      ::xsd::cxx::tree::one< RadiusType > radius_;
      static const RadiusType radius_default_value_;
    };

    class WallsType: public ::xml_schema::Type
    {
      public:
      // wall
      // 
      typedef ::AT::XML::RectangleType WallType;
      typedef ::xsd::cxx::tree::sequence< WallType > WallSequence;
      typedef WallSequence::iterator WallIterator;
      typedef WallSequence::const_iterator WallConstIterator;
      typedef ::xsd::cxx::tree::traits< WallType, char > WallTraits;

      const WallSequence&
      wall () const;

      WallSequence&
      wall ();

      void
      wall (const WallSequence& s);

      // Constructors.
      //
      WallsType ();

      WallsType (const ::xercesc::DOMElement& e,
                 ::xml_schema::Flags f = 0,
                 ::xml_schema::Container* c = 0);

      WallsType (const WallsType& x,
                 ::xml_schema::Flags f = 0,
                 ::xml_schema::Container* c = 0);

      virtual WallsType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~WallsType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      WallSequence wall_;
    };

    class FlowType: public ::xml_schema::Type
    {
      public:
      // velocity
      // 
      typedef ::AT::XML::VelocityType VelocityType;
      typedef ::xsd::cxx::tree::sequence< VelocityType > VelocitySequence;
      typedef VelocitySequence::iterator VelocityIterator;
      typedef VelocitySequence::const_iterator VelocityConstIterator;
      typedef ::xsd::cxx::tree::traits< VelocityType, char > VelocityTraits;

      const VelocitySequence&
      velocity () const;

      VelocitySequence&
      velocity ();

      void
      velocity (const VelocitySequence& s);

      // Constructors.
      //
      FlowType ();

      FlowType (const ::xercesc::DOMElement& e,
                ::xml_schema::Flags f = 0,
                ::xml_schema::Container* c = 0);

      FlowType (const FlowType& x,
                ::xml_schema::Flags f = 0,
                ::xml_schema::Container* c = 0);

      virtual FlowType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~FlowType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      VelocitySequence velocity_;
    };

    class LevelType: public ::xml_schema::Type
    {
      public:
      // mainLauncher
      // 
      typedef ::AT::XML::LauncherType MainLauncherType;
      typedef ::xsd::cxx::tree::traits< MainLauncherType, char > MainLauncherTraits;

      const MainLauncherType&
      mainLauncher () const;

      MainLauncherType&
      mainLauncher ();

      void
      mainLauncher (const MainLauncherType& x);

      void
      mainLauncher (::std::auto_ptr< MainLauncherType > p);

      // optionalLaunchers
      // 
      typedef ::AT::XML::LaunchersType OptionalLaunchersType;
      typedef ::xsd::cxx::tree::traits< OptionalLaunchersType, char > OptionalLaunchersTraits;

      const OptionalLaunchersType&
      optionalLaunchers () const;

      OptionalLaunchersType&
      optionalLaunchers ();

      void
      optionalLaunchers (const OptionalLaunchersType& x);

      void
      optionalLaunchers (::std::auto_ptr< OptionalLaunchersType > p);

      // receiver
      // 
      typedef ::AT::XML::ReceiverType ReceiverType;
      typedef ::xsd::cxx::tree::traits< ReceiverType, char > ReceiverTraits;

      const ReceiverType&
      receiver () const;

      ReceiverType&
      receiver ();

      void
      receiver (const ReceiverType& x);

      void
      receiver (::std::auto_ptr< ReceiverType > p);

      // walls
      // 
      typedef ::AT::XML::WallsType WallsType;
      typedef ::xsd::cxx::tree::traits< WallsType, char > WallsTraits;

      const WallsType&
      walls () const;

      WallsType&
      walls ();

      void
      walls (const WallsType& x);

      void
      walls (::std::auto_ptr< WallsType > p);

      // flow
      // 
      typedef ::AT::XML::FlowType FlowType;
      typedef ::xsd::cxx::tree::traits< FlowType, char > FlowTraits;

      const FlowType&
      flow () const;

      FlowType&
      flow ();

      void
      flow (const FlowType& x);

      void
      flow (::std::auto_ptr< FlowType > p);

      // rate
      // 
      typedef ::xml_schema::Float RateType;
      typedef ::xsd::cxx::tree::traits< RateType, char > RateTraits;

      const RateType&
      rate () const;

      RateType&
      rate ();

      void
      rate (const RateType& x);

      static const RateType&
      rateDefaultValue ();

      // nextLevel
      // 
      typedef ::xml_schema::String NextLevelType;
      typedef ::xsd::cxx::tree::optional< NextLevelType > NextLevelOptional;
      typedef ::xsd::cxx::tree::traits< NextLevelType, char > NextLevelTraits;

      const NextLevelOptional&
      nextLevel () const;

      NextLevelOptional&
      nextLevel ();

      void
      nextLevel (const NextLevelType& x);

      void
      nextLevel (const NextLevelOptional& x);

      void
      nextLevel (::std::auto_ptr< NextLevelType > p);

      // Constructors.
      //
      LevelType (const MainLauncherType&,
                 const OptionalLaunchersType&,
                 const ReceiverType&,
                 const WallsType&,
                 const FlowType&);

      LevelType (::std::auto_ptr< MainLauncherType >&,
                 ::std::auto_ptr< OptionalLaunchersType >&,
                 ::std::auto_ptr< ReceiverType >&,
                 ::std::auto_ptr< WallsType >&,
                 ::std::auto_ptr< FlowType >&);

      LevelType (const ::xercesc::DOMElement& e,
                 ::xml_schema::Flags f = 0,
                 ::xml_schema::Container* c = 0);

      LevelType (const LevelType& x,
                 ::xml_schema::Flags f = 0,
                 ::xml_schema::Container* c = 0);

      virtual LevelType*
      _clone (::xml_schema::Flags f = 0,
              ::xml_schema::Container* c = 0) const;

      virtual 
      ~LevelType ();

      // Implementation.
      //
      protected:
      void
      parse (::xsd::cxx::xml::dom::parser< char >&,
             ::xml_schema::Flags);

      protected:
      ::xsd::cxx::tree::one< MainLauncherType > mainLauncher_;
      ::xsd::cxx::tree::one< OptionalLaunchersType > optionalLaunchers_;
      ::xsd::cxx::tree::one< ReceiverType > receiver_;
      ::xsd::cxx::tree::one< WallsType > walls_;
      ::xsd::cxx::tree::one< FlowType > flow_;
      ::xsd::cxx::tree::one< RateType > rate_;
      static const RateType rate_default_value_;
      NextLevelOptional nextLevel_;
    };
  }
}

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

namespace AT
{
  namespace XML
  {
    // Parse a URI or a local file.
    //

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (const ::std::string& uri,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (const ::std::string& uri,
           ::xml_schema::ErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (const ::std::string& uri,
           ::xercesc::DOMErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    // Parse std::istream.
    //

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::std::istream& is,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::std::istream& is,
           ::xml_schema::ErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::std::istream& is,
           ::xercesc::DOMErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::std::istream& is,
           const ::std::string& id,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::std::istream& is,
           const ::std::string& id,
           ::xml_schema::ErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::std::istream& is,
           const ::std::string& id,
           ::xercesc::DOMErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    // Parse xercesc::InputSource.
    //

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::xercesc::InputSource& is,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::xercesc::InputSource& is,
           ::xml_schema::ErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::xercesc::InputSource& is,
           ::xercesc::DOMErrorHandler& eh,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    // Parse xercesc::DOMDocument.
    //

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (const ::xercesc::DOMDocument& d,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());

    ::std::auto_ptr< ::AT::XML::LevelType >
    level (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
           ::xml_schema::Flags f = 0,
           const ::xml_schema::Properties& p = ::xml_schema::Properties ());
  }
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace AT
{
  namespace XML
  {
    void
    operator<< (::xercesc::DOMElement&, const VectorType&);

    void
    operator<< (::xercesc::DOMElement&, const VelocityType&);

    void
    operator<< (::xercesc::DOMElement&, const RectangleType&);

    void
    operator<< (::xercesc::DOMElement&, const LauncherType&);

    void
    operator<< (::xercesc::DOMElement&, const LaunchersType&);

    void
    operator<< (::xercesc::DOMElement&, const ReceiverType&);

    void
    operator<< (::xercesc::DOMElement&, const WallsType&);

    void
    operator<< (::xercesc::DOMElement&, const FlowType&);

    void
    operator<< (::xercesc::DOMElement&, const LevelType&);

    // Serialize to std::ostream.
    //

    void
    level (::std::ostream& os,
           const ::AT::XML::LevelType& x, 
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           const ::std::string& e = "UTF-8",
           ::xml_schema::Flags f = 0);

    void
    level (::std::ostream& os,
           const ::AT::XML::LevelType& x, 
           ::xml_schema::ErrorHandler& eh,
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           const ::std::string& e = "UTF-8",
           ::xml_schema::Flags f = 0);

    void
    level (::std::ostream& os,
           const ::AT::XML::LevelType& x, 
           ::xercesc::DOMErrorHandler& eh,
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           const ::std::string& e = "UTF-8",
           ::xml_schema::Flags f = 0);

    // Serialize to xercesc::XMLFormatTarget.
    //

    void
    level (::xercesc::XMLFormatTarget& ft,
           const ::AT::XML::LevelType& x, 
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           const ::std::string& e = "UTF-8",
           ::xml_schema::Flags f = 0);

    void
    level (::xercesc::XMLFormatTarget& ft,
           const ::AT::XML::LevelType& x, 
           ::xml_schema::ErrorHandler& eh,
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           const ::std::string& e = "UTF-8",
           ::xml_schema::Flags f = 0);

    void
    level (::xercesc::XMLFormatTarget& ft,
           const ::AT::XML::LevelType& x, 
           ::xercesc::DOMErrorHandler& eh,
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           const ::std::string& e = "UTF-8",
           ::xml_schema::Flags f = 0);

    // Serialize to an existing xercesc::DOMDocument.
    //

    void
    level (::xercesc::DOMDocument& d,
           const ::AT::XML::LevelType& x,
           ::xml_schema::Flags f = 0);

    // Serialize to a new xercesc::DOMDocument.
    //

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
    level (const ::AT::XML::LevelType& x, 
           const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
           ::xml_schema::Flags f = 0);
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // OUTPUT_CONTENT_LEVELS_LEVEL_XML_H