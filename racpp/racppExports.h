#pragma once



#  if defined(RACPP_EXPORTS)
#    define RACPP_EXTERN  __declspec(dllexport)
#  else
#    define RACPP_EXTERN  __declspec(dllimport)
#  endif
