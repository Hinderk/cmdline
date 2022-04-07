
#ifndef __CMD_CMDOPTION_H
#define __CMD_CMDOPTION_H

#include <stdexcept>
#include <string>
#include <limits>


#define _TYPE(X) { static constexpr OptionType value = OptionType::X ; }



enum class OptionType { NONE, BOOLEAN, INTEGER, STRING, FLOAT, UNSIGNED } ;


template < typename T > struct TypeIndex _TYPE(NONE) ;

template<> struct TypeIndex< int8_t > _TYPE(INTEGER) ;
template<> struct TypeIndex< int16_t > _TYPE(INTEGER) ;
template<> struct TypeIndex< int32_t > _TYPE(INTEGER) ;
template<> struct TypeIndex< int64_t > _TYPE(INTEGER) ;
template<> struct TypeIndex< uint8_t > _TYPE(UNSIGNED) ;
template<> struct TypeIndex< uint16_t > _TYPE(UNSIGNED) ;
template<> struct TypeIndex< uint32_t > _TYPE(UNSIGNED) ;
template<> struct TypeIndex< uint64_t > _TYPE(UNSIGNED) ;
template<> struct TypeIndex< float > _TYPE(FLOAT) ;
template<> struct TypeIndex< double > _TYPE(FLOAT) ;
template<> struct TypeIndex< bool > _TYPE(BOOLEAN) ;
template<> struct TypeIndex< char > _TYPE(INTEGER) ;



class CmdOption {

  public:

    CmdOption( const std::string &name ) ;
    CmdOption( const char *name ) ;
    CmdOption( void ) ;

    template < class T > CmdOption( T val ) : value(), opt {}
    {
      type = TypeIndex<T>::value ;
      switch ( TypeIndex<T>::value )
      {
        case OptionType::INTEGER:
          opt.index = (int64_t) val ;
          break ;
        case OptionType::FLOAT:
          opt.fpval = (double) val ;
          break ;
        case OptionType::BOOLEAN:
          opt.logical = val ;
          break ;
        case OptionType::UNSIGNED:
          opt.number = (uint64_t) val ;
        default: ;
      }
    }

    template < class T > operator T( void ) const
    {
      switch ( TypeIndex<T>::value )
      {
        case OptionType::INTEGER:
          if ( opt.index <= (int64_t) std::numeric_limits<T>::max() &&
               (int64_t) std::numeric_limits<T>::lowest() <= opt.index )
            return (T) opt.index ;
          throw std::domain_error( "Option value out of range." ) ;
        case OptionType::FLOAT:
          if ( opt.fpval <= (double) std::numeric_limits<T>::max() &&
               (double) std::numeric_limits<T>::lowest() <= opt.fpval )
            return (T) opt.fpval ;
          throw std::domain_error( "Option value out of range." ) ;
        case OptionType::BOOLEAN:
          return opt.logical ;
        case OptionType::UNSIGNED:
          if ( opt.number <= (uint64_t) std::numeric_limits<T>::max() &&
               (uint64_t) std::numeric_limits<T>::lowest() <= opt.number )
            return (T) opt.number ;
          throw std::domain_error( "Option value out of range." ) ;
        default:
          throw std::domain_error( "Invalid cast from option." ) ;
      }
      return T {} ;
    }

    OptionType Type( void ) const { return type ; }

    const char *str( void ) const ;

  private:

    OptionType  type ;

    std::string value ;

    union {

      double      fpval ;
      int64_t     index ;
      uint64_t    number ;
      bool        logical ;

    } opt ;

} ;

#undef _TYPE

#endif     // __CMD_CMDOPTION_H
