#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

class ConexionBD {
private:
    MYSQL* conexion;
public:
    ConexionBD() {
        conexion = mysql_init(0);
        if (conexion) {
            cout << "Conexion creada correctamente" << endl;
        } else {
            cerr << "Error al crear la conexion" << endl;
        }
    }

    ~ConexionBD() {
        mysql_close(conexion);
        cout << "Conexion cerrada correctamente" << endl;
    }

    bool conectar(string localhost, string root, string admin, string adminzoo) {
        if (mysql_real_connect(conexion, "localhost", "root", "admin", "adminzoo", 0, nullptr, 0)) {
            cout << "Conexion exitosa a la base de datos " << adminzoo << endl;
            return true;
        } else {
            cerr << "Error al conectar a la base de datos: " << mysql_error(conexion) << endl;
            return false;
        }
    }

    bool ejecutarConsulta(string consulta) {
        if (mysql_query(conexion, consulta.c_str()) == 0) {
            cout << "Consulta ejecutada correctamente" << endl;
            return true;
        } else {
            cerr << "Error al ejecutar consulta: " << mysql_error(conexion) << endl;
            return false;
        }
    }

    MYSQL_RES* obtenerResultado() {
        return mysql_store_result(conexion);
    }

    void liberarResultado(MYSQL_RES* resultado) {
        mysql_free_result(resultado);
    }
};

int main() {
    ConexionBD conexion;
    if (conexion.conectar("localhost", "root", "admin", "adminzoo")) {
        while (true) {
            cout << "Selecciona una tabla:" << endl;
            cout << "1. Animales" << endl;
            cout << "2. Habitats" << endl;
            cout << "3. Salir" << endl;

            int opcionTabla;
            cin >> opcionTabla;

            if (opcionTabla == 3) {
                break;
            }

            string tabla;
            if (opcionTabla == 1) {
                tabla = "animales";
            } else if (opcionTabla == 2) {
                tabla = "habitat";
            } else {
                cout << "Opcion no valida" << endl;
                continue;
            }

            while (true) {
                cout << "Selecciona una opcion para la tabla " << tabla << ":" << endl;
                cout << "1. Mostrar datos" << endl;
                cout << "2. Insertar datos" << endl;
                cout << "3. Editar datos" << endl;
                cout << "4. Eliminar datos" << endl;
                cout << "5. Volver al menu anterior" << endl;

                int opcion;
                cin >> opcion;

                switch (opcion) {
                    case 1: {
                        if (conexion.ejecutarConsulta("SELECT * FROM " + tabla)) {
                        	
                            MYSQL_RES* resultado = conexion.obtenerResultado();
                            
                            if (resultado) {
                                MYSQL_ROW fila;
                                while ((fila = mysql_fetch_row(resultado))) {
                                    if (tabla == "animales") {
                                        cout << "ID: " << fila[0] << " | Nombre: " << fila[1] << " | Nombre Cientifico: " << fila[2] << " | Especie: " << fila[3] << " | Sexo: " << fila[4] << endl;
                                    } else if (tabla == "habitat") {
                                        cout << "ID: " << fila[0] << " | Nombre: " << fila[1] << " | Clima: " << fila[2] << " | Vegetacion: " << fila[3] << " | Descripcion: " << fila[4] << endl;
                                    }
                                }
                                conexion.liberarResultado(resultado);
                            }
                        }
                        break;
                    }
                    case 2: {
                    	
                        string consulta;
                        
                        if (tabla == "animales") {
                            string nombre_comun, nombre_cientifico, especie, sexo;
                            cout << "Ingrese nombre común: ";
                            cin >> nombre_comun;
                            cout << "Ingrese nombre científico: ";
                            cin >> nombre_cientifico;
                            cout << "Ingrese especie: ";
                            cin >> especie;
                            cout << "Ingrese sexo: ";
                            cin >> sexo;
                            
                            
                            
                            

                            consulta = "INSERT INTO " + tabla + " (nombre_comun, nombre_cientifico, especie, sexo) VALUES ('" + nombre_comun + "', '" + nombre_cientifico + "', '" + especie + "', '" + sexo + "')";
                       
                        
                        
                        
                        
                        
					    } else if (tabla == "habitat") {
                            string nombre, clima, tipo_de_vegetacion_predominante, descripcion;
                            cout << "Ingrese nombre: ";
                            cin >> nombre;
                            cout << "Ingrese clima: ";
                            cin >> clima;
                            cout << "Ingrese tipo de vegetación predominante: ";
                            cin >> tipo_de_vegetacion_predominante;
                            cout << "Ingrese descripción: ";
                            cin >> descripcion;

                            consulta = "INSERT INTO " + tabla + " (nombre, clima, tipo_de_vegetacion_predominante, descripcion) VALUES ('" + nombre + "', '" + clima + "', '" + tipo_de_vegetacion_predominante + "', '" + descripcion + "')";
                        }
                        
                        
                        conexion.ejecutarConsulta(consulta);
                        break;
                    }
                    case 3: {
                    	
                        int id;
                        cout << "Ingrese ID del registro a editar: ";
                        cin >> id;
                        string consulta;
                            
                            if (tabla == "animales") {
                            string nombre_comun, nombre_cientifico, especie, sexo;
                            cout << "Ingrese nombre común: ";
                            cin >> nombre_comun;
                            cout << "Ingrese nombre científico: ";
                            cin >> nombre_cientifico;
                            cout << "Ingrese especie: ";
                            cin >> especie;
                            cout << "Ingrese sexo: ";
                            cin >> sexo;

                            
                            consulta = "UPDATE " + tabla + " SET nombre_comun = '" + nombre_comun + "', nombre_cientifico = '" + nombre_cientifico + "', especie = '" + especie + "', sexo = '" + sexo + "' WHERE animales_id = " + to_string(id);

					   
					   
					    } else if (tabla == "habitat") {
                            string nombre, clima, tipo_de_vegetacion_predominante, descripcion;
                            cout << "Ingrese nombre: ";
                            cin >> nombre;
                            cout << "Ingrese clima: ";
                            cin >> clima;
                            cout << "Ingrese tipo de vegetación predominante: ";
                            cin >> tipo_de_vegetacion_predominante;
                            cout << "Ingrese descripción: ";
                            cin >> descripcion;

                            consulta = "UPDATE " + tabla + " SET nombre = '" + nombre + "', clima = '" + clima + "', tipo_de_vegetacion_predominante = '" + tipo_de_vegetacion_predominante + "', descripcion = '" + descripcion + "' WHERE habitat_id = " + to_string(id);
                        }
                        
                        conexion.ejecutarConsulta(consulta);
                        break;
                    }
                    case 4: {
                    	
                    int id;
                    cout << "Ingrese ID del registro a eliminar: ";
                    cin >> id;
                    string consulta;
                    
                    if (tabla == "animales") {
                    	
                    consulta = "DELETE FROM " + tabla + " WHERE animales_id = " + to_string(id);
                    
                    } else if (tabla == "habitat") {
                    	
                    consulta = "DELETE FROM " + tabla + " WHERE id = " + to_string(id);
                    
                    }
                    conexion.ejecutarConsulta(consulta);
                    
                        break;
                    }
                    case 5: {
                        break;
                    }
                    default:
                        cout << "Opcion no valida" << endl;
                        break;
                }

                if (opcion == 5) {
                    break;
                }
            }
        }
    }

    return 0;
}

