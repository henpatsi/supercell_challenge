# TODO

- Remove reference to player from InputHandler, instead have player check InputHandler (singleton?) key states in its own update
- Make UI into its own class that is updated through the Game class, could also be updated from anywhere as values change if it is a singleton
- Redo InputHandler as in sfml test project
- Check which heap allocations are actually needed, and what could be stored on stack
