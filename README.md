# pipex 🔗

![42 School](https://img.shields.io/badge/42-Madrid-black?style=flat-square&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![Unix](https://img.shields.io/badge/Unix-FCC624?style=flat-square&logo=linux&logoColor=black)

**pipex** es un proyecto de 42 Madrid que replica el comportamiento de los pipes de Unix. El objetivo es crear un programa que simule el funcionamiento de un pipeline de comandos bash, conectando la salida de un comando con la entrada del siguiente.

> *"The beauty of Unix pipes lies in their simplicity and power."*

## 📋 Tabla de Contenidos

- [Sobre el Proyecto](#-sobre-el-proyecto)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Funcionalidades](#-funcionalidades)
- [Algoritmo](#-algoritmo)
- [Manejo de Errores](#-manejo-de-errores)
- [Recursos](#-recursos)
- [Autor](#-autor)

## 🎯 Sobre el Proyecto

Este proyecto forma parte del **Milestone 2** del cursus de 42 Madrid. pipex debe replicar el comportamiento del siguiente comando shell:

```bash
< file1 cmd1 | cmd2 > file2
```

El programa toma cuatro argumentos:
- `file1`: archivo de entrada
- `cmd1`: primer comando con sus parámetros
- `cmd2`: segundo comando con sus parámetros  
- `file2`: archivo de salida

### Objetivos de Aprendizaje

- Comprender el funcionamiento de los **pipes** en sistemas Unix
- Trabajar con **procesos hijo** y **fork()**
- Gestionar **file descriptors** y redirecciones
- Implementar manejo robusto de errores
- Dominar las funciones del sistema: `pipe()`, `fork()`, `execve()`, `dup2()`

## 🚀 Instalación

1. **Clona el repositorio:**
   ```bash
   git clone https://github.com/ravazque/pipex.git
   cd pipex
   ```

2. **Compila el proyecto:**
   ```bash
   make
   ```

3. **Compila con flags de debugging (opcional):**
   ```bash
   make debug
   ```

## 💻 Uso

### Uso Básico

```bash
./pipex file1 cmd1 cmd2 file2
```

### Ejemplos Prácticos

```bash
# Equivalente a: < infile grep "hello" | wc -l > outfile
./pipex infile "grep hello" "wc -l" outfile

# Equivalente a: < input.txt cat | sort > output.txt
./pipex input.txt "cat" "sort" output.txt

# Equivalente a: < numbers.txt sort -n | tail -5 > top5.txt
./pipex numbers.txt "sort -n" "tail -5" top5.txt
```

### Casos de Uso Avanzados

```bash
# Con comandos que requieren parámetros complejos
./pipex data.txt "cut -d, -f1" "sort -u" unique_fields.txt

# Con comandos de filtrado
./pipex log.txt "grep ERROR" "head -10" errors.txt
```

## ✨ Funcionalidades

### Características Principales

- ✅ **Pipe Implementation**: Conexión perfecta entre comandos
- ✅ **Process Management**: Manejo de procesos padre e hijo
- ✅ **File Handling**: Gestión correcta de archivos de entrada y salida
- ✅ **Error Management**: Manejo robusto de errores del sistema
- ✅ **Memory Safety**: Sin leaks de memoria
- ✅ **PATH Resolution**: Búsqueda automática de ejecutables en PATH

### Funciones del Sistema Utilizadas

- `pipe()` - Creación de pipes
- `fork()` - Creación de procesos hijo
- `execve()` - Ejecución de comandos
- `dup2()` - Duplicación de file descriptors
- `waitpid()` - Espera de procesos hijo
- `access()` - Verificación de permisos de archivos

## 🔧 Algoritmo

### Flujo de Ejecución

1. **Validación de Argumentos**
   - Verificar número correcto de parámetros
   - Validar existencia y permisos del archivo de entrada

2. **Configuración del Pipe**
   ```c
   int pipefd[2];
   pipe(pipefd);  // Crear pipe
   ```

3. **Primer Proceso Hijo (cmd1)**
   - Abrir archivo de entrada
   - Redirigir stdin al archivo
   - Redir stdout al pipe
   - Ejecutar primer comando

4. **Segundo Proceso Hijo (cmd2)**
   - Redirigir stdin al pipe
   - Abrir/crear archivo de salida
   - Redirigir stdout al archivo
   - Ejecutar segundo comando

5. **Proceso Padre**
   - Cerrar extremos del pipe
   - Esperar a ambos procesos hijo
   - Manejar códigos de salida

### Estructura del Programa

```
pipex/
├── src/
│   ├── pipex.c          # Función principal
│   ├── utils.c          # Funciones auxiliares
│   ├── path.c           # Resolución de PATH
│   └── error.c          # Manejo de errores
├── include/
│   └── pipex.h          # Headers y definiciones
├── libft/               # Biblioteca personal (si aplica)
└── Makefile
```

## ⚠️ Manejo de Errores

El programa maneja los siguientes tipos de errores:

- **Argumentos inválidos**: Número incorrecto de parámetros
- **Archivos no encontrados**: file1 no existe o no es accesible
- **Permisos insuficientes**: Sin permisos de lectura/escritura
- **Comandos no encontrados**: cmd1 o cmd2 no existen en PATH
- **Fallos del sistema**: Errores en pipe(), fork(), execve()

### Códigos de Salida

- `0`: Ejecución exitosa
- `1`: Error general
- `127`: Comando no encontrado
- `126`: Comando no ejecutable

## 📚 Recursos

### Funciones Clave

- [`pipe(2)`](https://man7.org/linux/man-pages/man2/pipe.2.html) - Crear pipe
- [`fork(2)`](https://man7.org/linux/man-pages/man2/fork.2.html) - Crear proceso hijo
- [`execve(2)`](https://man7.org/linux/man-pages/man2/execve.2.html) - Ejecutar programa
- [`dup2(2)`](https://man7.org/linux/man-pages/man2/dup.2.html) - Duplicar file descriptor

### Documentación Útil

- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/)
- [Linux Manual Pages](https://man7.org/linux/man-pages/)

## 🏆 Estado del Proyecto

- **Fecha de finalización**: *En desarrollo*
- **Calificación**: *Pendiente*
- **Status**: ✅ Funcional

## 👨‍💻 Autor

**Raúl Vázquez Pérez** - *42 Madrid*

- 📧 Email: [rk.raul1306@gmail.com](mailto:rk.raul1306@gmail.com)
- 🔗 LinkedIn: [Raúl Vázquez Pérez](https://www.linkedin.com/in/ra%C3%BAl-v%C3%A1zquez-p%C3%A9rez-46a122368/)
- 🐙 GitHub: [@ravazque](https://github.com/ravazque)

---

*Proyecto desarrollado como parte del curriculum de 42 Madrid - 2024*

**[⬆ Volver arriba](#pipex-)**
