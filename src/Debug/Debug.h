#ifndef SRC_DEBUG_H
#define SRC_DEBUG_H


#include <iostream>
#include <sstream>
#include <string_view>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// MACROS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*********************** Macro Overload Implementation ************************/

#define CONCAT(x, y) x ## y
#define SELECT(macro, num) CONCAT(macro ## _, num)
#define VA_SIZE(_0, _1, _2, _3, count, ...) count // ad nauseam
#define COMPOSE(name, args) name args
#define EXPAND() ,,,
#define VA_MACRO(macro, ...)                                                   \
    SELECT(                                                                    \
        macro,                                                                 \
        COMPOSE(                                                               \
            VA_SIZE,                                                           \
            (EXPAND __VA_ARGS__ (), 0, 3, 2, 1)))(__VA_ARGS__)

/* 
    Notes:
        - How To Use:
            #define NAME(...) VA_MACRO(NAME, __VA_ARGS__)
            #define NAME_<Number>(<Arguments>) <String>

        - Number of possible arguments is determined by number of arguments
        added to VA_SIZE

        - The EXPAND macro must consist of the same number of commas as the
        number of arguments determined by VA_SIZE

        - The VA_MACRO macro's number arguments must match the VA_SIZE number
        arguments
*/

/*********************************** Macros ***********************************/

#define THROW_ERROR(...) debug::throwError(__FILE__, __LINE__, __VA_ARGS__)
#define STRINGIFY(x) (#x)

/******************************************************************************/

#ifndef NDEBUG  // Debug Mode

    #define DEBUG_ASSERT(x)                                                    \
    {                                                                          \
        if (!(x))                                                              \
            THROW_ERROR("%() Assertion Error: '%'", __FUNCTION__, #x);         \
    }
    #define DEBUG_PRINT(...)  debug::print(__VA_ARGS__)

#else           // Release Mode

    #define DEBUG_ASSERT(x)
    #define DEBUG_PRINT(...)

#endif


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONCEPTS ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template<typename T>
concept Printable = requires (T t)
{
    {std::cout << t} -> std::same_as<std::ostream&>;
};


template<typename T>
concept Stringable = requires (std::ostringstream oss, T t)
{
    oss << t;
};


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace debug
{
    /*************************** Template Functions ***************************/

    /* 
        Returns Formatted String
    */
    template <Stringable ...Args>
    std::string str(std::string_view format, Args&&... args)
    {
        size_t numOfArgs {sizeof...(Args)}, argIndex {};
        std::stringstream sstream {};

        /************************ String Construction *************************/
        
        auto iter {format.begin()};

        ([&] ()
        {
            if (argIndex < numOfArgs)
            {
                for (; iter != format.end(); ++iter)
                {
                    if (*iter == '%')
                    {
                        sstream << args;
                        ++argIndex;
                        ++iter;
                        return;
                    }
                    else
                        sstream << *iter;
                }
            }
        }(), ...);

        for (; iter != format.end(); ++iter)
            sstream << *iter;

        /************************* String Validation **************************/
    
        if (argIndex != numOfArgs)
        {
            std::cout << "\n[ DEBUG ] str() Error: Number of variables in "
                "format string exceeded number of arguments\n";

            std::abort();
        }

        /**********************************************************************/   
    
        return sstream.str();
    }


    /*
        Logs message
    */
    template <Printable T>
    void print(const T& message)
    {
        std::cout << '\n' << message << '\n';
    }

    template <Printable T>
    void print(const T&& message)
    {
        std::cout << '\n' << message << '\n';
    }


    /*
        Logs formatted message
    */
    template <Stringable ...Args>
    void print(std::string_view format, Args&&... args)
    {
        // Print Formatted Message
        print(str(format, args...));
    }

    /*
        Throws a runtime error with the formatted message
    */
    template <Stringable ...Args>
    void throwError(
        std::string_view file,
        int line,
        std::string_view format,
        Args&&... args)
    {
        // Throw Error
        throw std::runtime_error(
            debug::str(
                debug::str("% | % (%)", format, file, line),
                args...));
    }
}


#endif // SRC_DEBUG_H
