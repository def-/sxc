//enum ErrorType/*{{{*/

/// The exit codes for errors (or starting points for error ranges).
enum ErrorType
{
    ErrorNoError = 0, //< No error occured.
    ErrorGeneral = 1,
    // Parameter errors.
    ErrorParametersInvalid = 10,
    ErrorJidInvalid = 12,
};
/*}}}*/
