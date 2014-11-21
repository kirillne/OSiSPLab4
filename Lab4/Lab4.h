// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LAB4_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LAB4_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LAB4_EXPORTS
#define LAB4_API __declspec(dllexport)
#else
#define LAB4_API __declspec(dllimport)
#endif

// This class is exported from the Lab4.dll
class LAB4_API CLab4 {
public:
	CLab4(void);
	// TODO: add your methods here.
};

extern LAB4_API int nLab4;

LAB4_API int fnLab4(void);
