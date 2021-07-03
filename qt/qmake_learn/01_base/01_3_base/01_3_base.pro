TEMPLATE = app
LANGUAGE  = c++
CONFIG += cmdline precompile_header
QT +=widgets

# use Precompiled headers (PCH)
PRECOMPILED_HEADER = stable.h

HEADERS = stable.h \
		  mydialog.h \
		  myobject.h 
SOURCES  = main.cpp \
			mydialog.cpp
			myobject.cpp
			util.cpp
			moc_mydialog.cpp
			
FORMS 	= mydialog.ui 