
#ifndef __CMD_CMDOPTION_H
#define __CMD_CMDOPTION_H

#include <cstdint>
#include <cstddef>
#include <typeinfo>


#define __ID(T,N)  TypeIndex<T> { static constexpr int value = N ; }
#define __TD(N,T) TypeDefinition< N > { typedef T Type ; }


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

  template < int n > struct TypeDefinition { typedef void Type ; } ;

  template<> struct __TD( CMD_INT16_T, int16_t ) ;
  template<> struct __TD( CMD_INT32_T, int32_t ) ;
  template<> struct __TD( CMD_INT64_T, int64_t ) ;
  template<> struct __TD( CMD_FLOAT32_T, float ) ;
  template<> struct __TD( CMD_FLOAT64_T, double ) ;
  template<> struct __TD( CMD_FLOAT96_T, long double ) ;
  template<> struct __TD( CMD_UINT16_T, uint16_t ) ;
  template<> struct __TD( CMD_UINT32_T, uint32_t ) ;
  template<> struct __TD( CMD_UINT64_T, uint64_t ) ;
  template<> struct __TD( CMD_BOOL_T, bool ) ;
  template<> struct __TD( CMD_CHAR_T, char ) ;
  template<> struct __TD( CMD_INT8_T, int8_t ) ;
  template<> struct __TD( CMD_UINT8_T, uint8_t ) ;
  template<> struct __TD( CMD_STRING_T, const char * ) ;

}  // End of namespace __CMD



class CmdOption {

    template < int Index >
    using DataType = typename __CMD::TypeDefinition< Index >::Type ;

  public:

    struct DataHandle {

      virtual ~DataHandle( void ) {} ;

      virtual int Type( void ) const  = 0 ;

    } ;

    virtual ~CmdOption( void ) {}

    int Type( void ) const
    {
      return Handle ? Handle -> Type() : CMD_UNDEFINED_T ;
    }

    template < typename T > operator T( void ) const
    {
      if ( this -> Type() == __CMD::TypeIndex<T>::value )
      {
        return static_cast< DataItem<T>* >( Handle ) -> Item ;
      }
      throw std::bad_cast() ;
    }

  protected:

    CmdOption( void ) : Handle( NULL ) {}

    template < typename T >
    DataHandle* CopyItem( const DataHandle *In )
    {
      return new DataItem<T>(static_cast<const DataItem<T>*>(In)->Item) ;
    }

    template < int Index >
    DataHandle* CreateCopy( const DataHandle *Input )
    {
      return CopyItem< DataType<Index> > ( Input ) ;
    }

    template < typename T >
    struct DataItem : public DataHandle {

      DataItem( const T &val ) : Item( val ) {}

      virtual int Type( void ) const
      {
        return __CMD::TypeIndex<T>::value ;
      }

      const T Item ;

    } ;

    void Destroy( CmdOption *COP ) { COP -> Discard( Handle ) ; }

    DataHandle* Create( int Type, const DataHandle *Data, CmdOption *COP )
    {
      return COP -> Copy( Type, Data ) ;
    }

    virtual void Discard( const DataHandle * ) = 0 ;
    virtual DataHandle* Copy( int, const DataHandle * ) = 0 ;

  protected:

    DataHandle *Handle ;

} ;

#undef __ID
#undef __TD

#endif     // __CMD_CMDOPTION_H
