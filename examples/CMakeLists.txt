set(amb_examples configwebsocketsink configwebsocketsource configwheel databaseconfig databasesource dbusconfig exampleconfig
    gpsdconfig obdsourceconfig opencvluxconfig opencvdbusconfig qtmainloopconfig)

install (FILES ${amb_examples} DESTINATION /etc/ambd/examples)

