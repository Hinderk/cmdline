
#ifndef __CMD_CMDOPTION_H
#define __CMD_CMDOPTION_H

#include <cstdint>
#include <sstream>
#include <cstring>
#include <cstddef>
#include <typeinfo>


#define __ID(T,N)  TypeIndex<T> { static constexpr int value = N ; }


#define     CMD_UNDEFINED_T   0x00
#define          CMD_BOOL_T   0x01
#define          CMD_INT8_T   0x02
#define         CMD_INT16_T   0x03
#define         CMD_INT32_T   0x04
#define         CMD_INT64_T   0x05
#define        CMD_INT128_T   0x06
#define         CMD_UINT8_T   0x07
#define        CMD_UINT16_T   0x08
#define        CMD_UINT32_T   0x09
#define        CMD_UINT64_T   0x0a
#define       CMD_UINT128_T   0x0b
#define       CMD_FLOAT32_T   0x0c
#define       CMD_FLOAT64_T   0x0d
#define       CMD_FLOAT96_T   0x0e
#define        CMD_STRING_T   0x0f
#define         CMD_ARRAY_T   0x12
#define          CMD_CHAR_T   0x13


namespace __CMD {

  template < typename T > struct TypeIndex
  {
    static constexpr int value = CMD_UNDEFINED_T ;
  } ;

  template<> struct __ID( int16_t, CMD_INT16_T ) ;
  template<> struct __ID( int32_t, CMD_INT32_T ) ;
  template<> struct __ID( int64_t, CMD_INT64_T ) ;
  template<> struct __ID( float, CMD_FLOAT32_T ) ;
  template<> struct __ID( double, CMD_FLOAT64_T ) ;
  template<> struct __ID( long double, CMD_FLOAT96_T ) ;
  template<> struct __ID( uint16_t, CMD_UINT16_T ) ;
  template<> struct __ID( uint32_t, CMD_UINT32_T ) ;
  template<> struct __ID( uint64_t, CMD_UINT64_T ) ;
  template<> struct __ID( bool, CMD_BOOL_T ) ;
  template<> struct __ID( char, CMD_CHAR_T ) ;
  template<> struct __ID( int8_t, CMD_INT8_T ) ;
  template<> struct __ID( uint8_t, CMD_UINT8_T ) ;
  template<> struct __ID( const char *, CMD_STRING_T ) ;


  struct DataHandle {

    virtual ~DataHandle( void ) {} ;

    virtual void Discard( void ) = 0 ;
    virtual DataHandle *Copy( void ) const = 0 ;
    virtual int Type( void ) const = 0 ;
    virtual std::string GetString( void ) const = 0 ;

  } ;


  template < typename T >
  struct DataItem : public DataHandle {

    DataItem( const T &val ) : Item( val ) {}

    void Discard( void )  { delete this ; }

    DataHandle* Copy( void ) const
    {
      return new DataItem<T>( Item ) ;
    }

    int Type( void ) const
    {
      return __CMD::TypeIndex<T>::value ;
    }

    std::string GetString( void ) const
    {
      std::stringstream out ;
      out << Item ;
      return out.str() ;
    }

    const T Item ;

  } ; 


  template<>
  struct DataItem<const char *> : public DataHandle {

    DataItem( const char *String )
    {
      Item = String ? strdup( String ) : NULL ;
    }

    void Discard( void )
    { 
      if ( Item )  free( (void*) Item ) ;
      delete this ;
    }

    DataHandle *Copy( void ) const
    {
      return new DataItem<const char *>( Item ) ;
    }

    int Type( void ) const { return CMD_STRING_T ; }

    std::string GetString( void ) const
    {
      return std::string( Item ) ;
    }

    const char *Item ;

  } ;


}  // End of namespace __CMD



class CmdOption {

  public:

    virtual ~CmdOption( void ) {}

    int Type( void ) const
    {
      return Handle ? Handle -> Type() : CMD_UNDEFINED_T ;
    }

    std::string GetString( void ) const
    {
      return Handle ? Handle -> GetString() : "" ;
    }

    template < typename T > operator T( void ) const
    {
      if ( Type() == __CMD::TypeIndex<T>::value )
      {
        return static_cast< __CMD::DataItem<T>* >( Handle ) -> Item ;
      }
      throw std::bad_cast() ;
    }

  protected:

    CmdOption( void ) : Handle( NULL ) {}

    __CMD::DataHandle *Handle ;

} ;

#undef __ID

#endif     // __CMD_CMDOPTION_H
