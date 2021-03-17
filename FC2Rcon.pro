TEMPLATE = subdirs

SUBDIRS += \
    server \
    client

server.subdir = src/server
client.subdir = src/client
