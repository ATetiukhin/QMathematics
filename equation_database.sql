/*
mysql --user=root -p -vvv < equation_database.sql
*/

/* Delete data base */
DROP DATABASE IF EXISTS equation;

/* Delete table */
-- DROP TABLE IF EXISTS `type_task`;

CREATE DATABASE IF NOT EXISTS `equation`
CHARACTER SET utf8 COLLATE utf8_general_ci;
SET storage_engine = INNODB;

-- SHOW DATABASES;

USE equation;
-- SHOW TABLES;

/* CREATE TABLE  */

-- private table
CREATE TABLE IF NOT EXISTS `type_task` (
  `id_type_task` INT(10)      NOT NULL,
  `name_task`    VARCHAR(255) NOT NULL,

  PRIMARY KEY (`id_type_task`)
);

-- private table
CREATE TABLE IF NOT EXISTS `methods` (
  `id_method`      INT(10)      NOT NULL,
  `type_task`      INT(10)      NOT NULL,
  `method_name`    varchar(255) NOT NULL,
  `path_to_method` varchar(255) NOT NULL,

  PRIMARY KEY (`id_method`),
  FOREIGN KEY (`type_task`) REFERENCES `type_task`(`id_type_task`)
);

-- private table
CREATE TABLE IF NOT EXISTS `parameters_method` (
  `id_method_parameters` INT(10)      NOT NULL,
  `method`               INT(10)      NOT NULL,
  `parameters_name`      varchar(255) NOT NULL,
  `note`                 varchar(255) NOT NULL,

  PRIMARY KEY (`id_method_parameters`),
  FOREIGN KEY (`method`) REFERENCES `methods`(`id_method`)
);

CREATE TABLE IF NOT EXISTS `expressions` (
  `id_expression`  INT(10)      NOT NULL AUTO_INCREMENT,
  `type_task`      INT(10)      NOT NULL,
  `expression`     varchar(255) NOT NULL,

  PRIMARY KEY (`id_expression`),
  FOREIGN KEY (`type_task`) REFERENCES `type_task`(`id_type_task`)
);

-- The value of the parameters
CREATE TABLE IF NOT EXISTS `parameters_values` (
  `id_session` INT(10) NOT NULL AUTO_INCREMENT,
  `method`     INT(10) NOT NULL,
  `expression` INT(10) NOT NULL,
  `parameter`  INT(10) NOT NULL,
  `value`      DOUBLE  NOT NULL,

  PRIMARY KEY (`id_session`, `method`),
  FOREIGN KEY (`method`)     REFERENCES `methods`            (`id_method`),
  FOREIGN KEY (`expression`) REFERENCES `expressions`        (`id_expression`),
  FOREIGN KEY (`parameter`)  REFERENCES `parameters_method`  (`id_method_parameters`)
);

CREATE TABLE IF NOT EXISTS `result` (
  `number_component`  INT(10) NOT NULL,
  `session`           INT(10) NOT NULL,
  `method`            INT(10) NOT NULL,
  `answer`            DOUBLE  NOT NULL,

  FOREIGN KEY (`session`) REFERENCES `parameters_values` (`id_session`),
  FOREIGN KEY (`method`)  REFERENCES `methods`           (`id_method`)
);

CREATE TABLE IF NOT EXISTS `sample` (
  `id_sample` INT(10)      NOT NULL,
  `name_sample` VARCHAR(255) NOT NULL,

  PRIMARY KEY (`id_sample`)
);

CREATE TABLE IF NOT EXISTS `sampling_data` (
  `sample`        INT(10)      NOT NULL,
  `serial_number` VARCHAR(255) NOT NULL,
  `value`         DOUBLE       NOT NULL,

  PRIMARY KEY (`sample`, `serial_number`),
  FOREIGN KEY (`sample`) REFERENCES `sample` (`id_sample`) 
);

-- ---------------------------------------------------

INSERT INTO `type_task`
  (`id_type_task`, `name_task`)
VALUES
  (0, 'Equation'),
  (1, 'Probability');

-- ---------------------------------------------------

INSERT INTO `methods`
  (`id_method`, `type_task`, `method_name`, `path_to_method`)
VALUES
  (0, 0, "Bisection", "C:\\plugins\\bisection.dll"),
  (1, 1, "Cdbinrnk", "C:\\plugins\\cdbinrnk.dll");

-- ---------------------------------------------------

INSERT INTO `parameters_method`
  (`id_method_parameters`, `method`, `parameters_name`, `note`)
VALUES
  (0, 0, "x_start", "comment 1"),
  (1, 0, "x_end",   "comment 2"),
  (2, 0, "eps",     "comment 3");

-- ---------------------------------------------------

INSERT INTO `sample`
  (`id_sample`, `name_sample`)
VALUES
  (0, 'Test 1');

-- ---------------------------------------------------  

INSERT INTO `sampling_data`
  (`sample`, `serial_number`, `value`)
VALUES
  (0, 0, 0),
  (0, 1, 10),
  (0, 2, 20),
  (0, 3, 30),
  (0, 4, 40);

-- ---------------------------------------------------  

-- SELECT * FROM `type_task`;
-- SELECT * FROM `methods`;
-- SELECT * FROM `parameters_method`;
