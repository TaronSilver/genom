QT += widgets

HEADERS += \
    Matrix.hpp \
    Sequence.hpp \
    utility.hpp \
    window.hpp \
    askdouble.hpp \
    askposandlength.hpp \
    savematrix.hpp \
    savesequence.hpp \
    askbaseprobability.hpp \
    resultswindow.hpp

SOURCES += \
    mainQt.cpp \
    window.cpp \
    Matrix.cpp \
    Sequence.cpp \
    utility.cpp \
    askdouble.cpp \
    askposandlength.cpp \
    savematrix.cpp \
    resultswindow.cpp \
    savesequence.cpp \
    askbaseprobability.cpp \
    user_interactionQt.cpp

FORMS += \
    window.ui \
    askdouble.ui \
    askposandlength.ui \
    savematrix.ui \
    resultswindow.ui \
    savesequence.ui \
    askbaseprobability.ui
