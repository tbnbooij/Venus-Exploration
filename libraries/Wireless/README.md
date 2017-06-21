# Wireless

## Wireless::Wireless()
Empty constructor, but needed for accessing the functions.

## Wireless::send(char msg)
Send a message; no return value.

## Wireless::read()
Read the received character (A-Z).

Return value depends on circumstances:
1. **-1** if no message was received
2. **-2** if the message was corrupted
3. **>0** if a character was received
