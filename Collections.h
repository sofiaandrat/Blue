#ifndef COLLECTIONS_H
#define COLLECTIONS_H

enum Actions
{
    LOGIN = 1,
    LOGOUT = 2,
    MOVE = 3,
    UPGRADE = 4,
    TURN = 5,
    PLAYER = 6,
    GAMES = 7,
    MAP = 10
};

enum Result
{
    OKEY = 0,
    BAD_COMMAND = 1,
    RESOURCE_NOT_FOUND = 2,
    ACCESS_DENIED = 3,
    INAPPROPRIATE_GAME_STATE = 4,
    TIMEOUT = 5,
    INTERNAL_SERVER_ERROR = 500
};

/*struct ActionMessage
{
    Action actionCode;
    size_t dataLength;
    QChar data[];
};*/


#endif // COLLECTIONS_H
