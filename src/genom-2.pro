QT += widgets

HEADERS += \
    Matrix.hpp \
    procedures.hpp \
    resultsWindow.hpp \
    saveSequence.hpp \
    Sequence.hpp \
    user_interaction.hpp \
    utility.hpp \
    window.hpp \
    matrixFromSequence.hpp \
    sequenceFromMatrix.hpp

SOURCES += \
    mainQt.cpp \
    Matrix.cpp \
    procedures.cpp \
    resultsWindow.cpp \
    saveSequence.cpp \
    Sequence.cpp \
    user_interactionQt.cpp \
    utility.cpp \
    window.cpp \
    matrixFromSequence.cpp \
    sequenceFromMatrix.cpp

FORMS += \
    resultsWindow.ui \
    saveSequence.ui \
    window.ui \
    matrixFromSequence.ui \
    sequenceFromMatrix.ui
