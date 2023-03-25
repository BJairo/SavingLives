USE NASA_V;

create table PACIENTE(
id_paciente int AUTO_INCREMENT, 
nombre VARCHAR(20),
apellidos VARCHAR(20), 
fecha_nacimiento date,
sexo VARCHAR(10),
contacto INTEGER,
PRIMARY KEY(id_paciente)
);

insert into PACIENTE values
(1, 'Downs', 'Marsha', '1975-03-21', 'Femenino' , '912563256');


create table DISCAPIDAD(
id_paciente int AUTO_INCREMENT,
discapacidad VARCHAR(20),
PRIMARY KEY(id_paciente, discapacidad),
FOREIGN KEY(id_paciente) REFERENCES PACIENTE(id_paciente)
);

insert into DISCAPIDAD values
(1, 'Esclerosis múltiple');

create table S_ACELEROMETRO(
id_acelerometro int AUTO_INCREMENT,
id_paciente int,
x FLOAT(4,2),
y FLOAT(4,2),
z FLOAT(4,2),
num_caidas INTEGER,
timestamp datetime DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY(id_acelerometro),
FOREIGN KEY(id_paciente) REFERENCES PACIENTE(id_paciente)
);

create table S_ULTRASONICA(
id_ultrasonico int AUTO_INCREMENT,
id_paciente int,
distancia FLOAT(4,2),
num_choques INTEGER,
timestamp datetime DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY(id_ultrasonico),
FOREIGN KEY(id_paciente) REFERENCES PACIENTE(id_paciente)
);

