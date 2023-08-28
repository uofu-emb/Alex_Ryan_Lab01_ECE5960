Change the source file to have the return value to be a global pointer.
Add the GPIO return value to the pointer to determine the validity through testing.
Looking at the return value will have different statuses at varying points in time.
    0-ok status flag
    *Any other value will indicate an error within the configuration of a GPIO pin.
View and keep track of the counter to see its size and if it's above a limit an error
will occur.