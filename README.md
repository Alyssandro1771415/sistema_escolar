# sistema_escolar

main(): The main function initializes the MySQL connection, displays a menu, and handles user input to navigate through different options.

showdata(): Displays the current date.

manha(), tarde(), noite(), integral(): Functions representing different shifts (morning, afternoon, evening, and full-time). Each function displays a shift-specific menu and handles user input.

cadastrar(): Allows the user to register new students or create new classes. It displays a submenu for choosing between student registration and class creation.

listClasses(): Retrieves and displays a list of classes based on the shift provided.

listStudents(): Retrieves and displays a list of students in a specific class.

obterTurmaID(): Retrieves the class ID for a given student.

obterNomeTurno(): Retrieves the class name and shift (turno) for a given class ID.

obterNotas(): Retrieves the grades for a given student.

searchStudent(): Searches for a specific student by ID and displays their information and report card.

novos_alunos(), insercao_encadeada_alunos(), limpar_lista_alunos(): Functions related to registering new students.

novas_turmas(), insercao_encadeada_turmas(), limpar_lista_turmas(): Functions related to creating new classes.

These functions provide the basic functionality for managing student records, generating reports, and interacting with the MySQL database.

Please note that the code assumes the presence of a MySQL database named "dados_escolares" and that the necessary MySQL Connector/C library is included.


![image](https://github.com/Alyssandro1771415/sistema_escolar/assets/100590540/850d0c3e-33b9-4138-b68c-52148ab77431)
