
primary::strlen
---------------

```
dTEMPLATE_CPP14 size_t strlen(s* text) dNOEXCEPT
{
    dASSERT(text);
    const s* p = text;
    while (*p != 0)
        ++p;
    return static_cast<size_t>(p - text);
}
```

old::strlen
-----------

pre11
  - ����� ������������ std::strlen
  - ����� ������������ std::wcslen

c++11, c++14
  - gcc: 
    - char   : __builtin_strlen 
    - wchar_t: std::wcslen
  - msvc:
    - char   : std::strlen
    - wchar_t: std::wcslen

c++17
  - gcc: 
    - char   : __builtin_strlen 
    - wchar_t: std::wcslen
  - msvc:
    if _HAS_CXX17:
      - char   : __builtin_strlen 
      - wchar_t: __builtin_wcslen 

      if __cpp_char8_t:
        if _HAS_U8_INTRINSICS:
          __builtin_u8strlen(_First);
        else
          primary:strlen
    else:
      - char   : std::strlen
      - wchar_t: std::wcslen

synopsis
--------

pre11
  - ����� ������������ std::strlen
  - ����� ������������ std::wcslen

c++11
  - ��� ��������� �������� ���������� constexpr
  - ��� ������� �������� ���������� std::strlen
  - ��� ���������� ���������� std::strlen
  - ��� ������� ���������� constexpr

c++14
  - ��� ���������� ���������� std::strlen
  - ��� �������� ���������� constexpr
  - ��� ������� ���������� constexpr

c++20
  - ��� constexpr ��������� ���������� constexpr
  - � ��������� ������� ���������� std::strlen


_HAS_CXX17
  __builtin_strlen
  __builtin_wcslen

  #ifdef __cpp_char8_t
        if constexpr (is_same_v<_Elem, char8_t>) {
        #if _HAS_U8_INTRINSICS
            return __builtin_u8strlen(_First);


