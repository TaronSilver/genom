QT += widgets

HEADERS += \
    Matrix.hpp \
    procedures.hpp \
    user_interaction.hpp \
    utility.hpp \
    window.hpp \
    matrixFromSequence.hpp \
    sequenceFromMatrix.hpp \
    resultsWindow.hpp \
    genomic_coordinates.hpp \
    askBaseProb.hpp \
    correlate.hpp

SOURCES += \
    mainQt.cpp \
    Matrix.cpp \
    procedures.cpp \
    user_interactionQt.cpp \
    utility.cpp \
    window.cpp \
    matrixFromSequence.cpp \
    sequenceFromMatrix.cpp \
    resultsWindow.cpp \
    genomic_coordinates.cpp \
    askBaseProb.cpp \
    correlate.cpp

FORMS += \
    window.ui \
    matrixFromSequence.ui \
    sequenceFromMatrix.ui \
    resultsWindow.ui \
    askBaseProb.ui \
    correlate.ui


INCLUDEPATH += ../logo
