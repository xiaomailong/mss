#Automate Unit test purpose, config unit test name and output dir
DEFINES += QT_NO_DEBUG_OUTPUT \
    QT_NO_INFO_OUTPUT \
    QT_NO_WARNING_OUTPUT
TARGET = $${TARGET}_mss_unit_tst
DESTDIR = $$OUT_PWD/../../../UnitTestTotal