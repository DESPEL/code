#include <cstring>
#include <functional>
#include <iostream>
#include <sstream>

// to_string - convertir cualquier tipo de dato a string (ostringstream)
template <typename T>
std::string to_string(T item)
{
    std::ostringstream strm;
    strm << item;
    return strm.str();
}

void separarNombre()
{
    std::string nombre, temp = "";
    std::cin.ignore();
    getline(std::cin, nombre);
    std::string partes[3];
    int i = 0;
    for (char& letra : nombre)
    {
        if (i > 2)
        {
            std::cout << "El nombre ingresado tiene mas de 3 palabras"
                      << std::endl;
            return;
        }
        if (letra == ' ')
        {
            partes[i] = temp;
            i++;
            temp = "";
        }
        else
        {
            temp += letra;
        }
    }
    std::string Nombre = partes[0];
    std::string PrimerApellido = partes[1];
    std::string SegundoApellido = temp;

    std::cout << "Nombre: " << Nombre << " Primer apellido: " << PrimerApellido
              << " Segundo apellido: " << SegundoApellido << std::endl;
}

// Remueve espaciso repetidos para contar las palabras correctamente
std::string fixStr(std::string texto)
{
    std::string temp = "";
    bool letp = false;
    for (int i = 0; i < texto.size(); i++)
    {
        if (texto[i] == ' ')
        {
            if (!letp)
                continue;
            letp = false;
        }
        else
        {
            letp = true;
        }
        temp += texto[i];
    }
    if (!letp)
        temp.pop_back();
    return temp;
}

int contarPalabras(std::string texto)
{
    int palabras = 1;
    // Elminar espacios repetidos y cosas asi.

    for (char& letra : fixStr(texto))
        if (letra == ' ')
            palabras++;

    return palabras;
}

// concatenar N llamada a funcion -> concatenarN(argumentos), cantidad de
// argumentos no relevante, tampoco tipo
std::string concatenarN() { return ""; };
template <typename T, typename... Types>
std::string concatenarN(T palabra, Types... palabras)
{
    return to_string(palabra) + " " + concatenarN(palabras...);
}

std::string mensaje(std::string nombre, std::string apellido1,
                    std::string apellido2, int edad)
{
    return "Hola, mi nombre es " + nombre + " " + apellido1 + " " + apellido2 +
           ", y mi edad es " + to_string(edad);
}

int edadMensaje(std::string mensaje)
{
    std::string edad = "";
    for (char& pos : mensaje)
    {
        if (pos >= '0' && pos <= '9')
        {
            edad += pos;
        }
    }
    std::stringstream conv(edad);
    int edadn = 0;
    conv >> edadn;
    return edadn;
}

typedef void (*ejercicios)();

void E1() { separarNombre(); }
void E2()
{
    std::string texto;
    std::cout << "Ingrese el texto a contar las palabras" << std::endl;
    std::cin.ignore();
    getline(std::cin, texto);
    std::cout << "La cantidad de palabras en el texto son: "
              << contarPalabras(texto) << std::endl;
}
void E3()
{
    std::cout << "Esta funcion se modifica desde el codigo fuente" << std::endl;
    std::cout << concatenarN("palabra1", "palabra2", "palabra3", "palabra4",
                             "palabra5")
              << std::endl;
}
void E4()
{
    std::string n, a1, a2;
    int edad;
    std::cout << "Ingrese su nombre" << std::endl;
    std::cin >> n;
    std::cout << "Ingrese su primer apellido" << std::endl;
    std::cin >> a1;
    std::cout << "Ingrese su segundo apellido" << std::endl;
    std::cin >> a2;
    std::cout << "Ingrese su edad" << std::endl;
    std::cin >> edad;
    std::cout << mensaje(n, a1, a2, edad) << std::endl;
}

void E5()
{
    std::string mensaje;
    std::cout << "Ingrese el mensaje que contiene su edad" << std::endl;
    std::cin.ignore();
    getline(std::cin, mensaje);
    std::cout << "La edad es: " << edadMensaje(mensaje) << std::endl;
}

ejercicios ejs[5] = {E1, E2, E3, E4, E5};

int main()
{
    int a = -1;
    while (true)
    {
        std::cout << "Ingrese la opcion del ejercicio" << std::endl;
        std::cout << "1) Separar nombre" << std::endl;
        std::cout << "2) Contar palabras" << std::endl;
        std::cout << "3) Concatenar palabras" << std::endl;
        std::cout << "4) Conversion y concatenacion" << std::endl;
        std::cout << "5) Extraer edad" << std::endl;
        std::cout << "6) Salir" << std::endl;
        std::cin >> a;
        while (a < 1 || a > 6)
        {
            std::cout << "Ingrese una opcion valida" << std::endl;
            std::cin >> a;
        }
        if (a == 6)
            break;
        ejs[a - 1]();
    }

    return 0;
}