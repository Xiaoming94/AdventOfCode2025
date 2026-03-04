#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_AOCLIBS
    #define AOCLIBS_PUBLIC __declspec(dllexport)
  #else
    #define AOCLIBS_PUBLIC __declspec(dllimport)
  #endif
#elif defined __OS2__
  #ifdef BUILDING_AOCLIBS
    #define AOCLIBS_PUBLIC __declspec(dllexport)
  #else
    #define AOCLIBS_PUBLIC
  #endif
#else
  #ifdef BUILDING_AOCLIBS
      #define AOCLIBS_PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define AOCLIBS_PUBLIC
  #endif
#endif

namespace aoclibs {

class AOCLIBS_PUBLIC Aoclibs {

public:
  Aoclibs();
  int get_number() const;

private:

  int number;

};

}

