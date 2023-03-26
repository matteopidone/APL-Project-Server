-- phpMyAdmin SQL Dump
-- version 5.1.4deb2+focal1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Creato il: Mar 25, 2023 alle 18:38
-- Versione del server: 10.3.37-MariaDB-0ubuntu0.20.04.1
-- Versione PHP: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `apl`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `holidays`
--

CREATE TABLE `holidays` (
  `id_user` varchar(255) NOT NULL,
  `date` date NOT NULL,
  `type` varchar(255) NOT NULL,
  `message` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `holidays`
--

INSERT INTO `holidays` (`id_user`, `date`, `type`, `message`) VALUES
('pidonematteo@hotmail.it', '2023-03-27', '1', 'Motivi personali'),
('pidonematteo@hotmail.it', '2023-03-28', '2', 'Impegni familiari'),
('tomasprifti99@gmail.com', '2023-03-29', '2', 'Devo andare dal meccanico'),
('tomasprifti99@gmail.com', '2023-04-13', '1', 'Visita oculistica'),
('pidonematteo@hotmail.it', '2023-04-14', '0', 'Devo comprare casa');
('tomasprifti99@gmail.com', '2023-04-14', '0', 'Devo accompagnare i miei figli');

-- --------------------------------------------------------

--
-- Struttura della tabella `users`
--

CREATE TABLE `users` (
  `email` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `surname` varchar(255) NOT NULL,
  `description` text DEFAULT NULL,
  `role` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dump dei dati per la tabella `users`
--

INSERT INTO `users` (`email`, `password`, `name`, `surname`, `description`, `role`) VALUES
('pidonematteo@hotmail.it', 'password', 'Matteo', 'Pidone', 'Programmatore informatico a tempo pieno presso Digit SrL', '0'),
('tomasprifti99@gmail.com', 'password', 'Tomas', 'Prifti', 'Data Analyst a tempo pieno presso Digit SrL', '0'),
('digit@amministrazione.it', 'pswadmin', 'Mario', 'Rossi', 'Amministratore Delegato a tempo pieno presso Digit SrL', '1');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `holidays`
--
ALTER TABLE `holidays`
  ADD PRIMARY KEY (`id_user`,`date`);

--
-- Indici per le tabelle `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`email`);

--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `holidays`
--
ALTER TABLE `holidays`
  ADD CONSTRAINT `holidays_ibfk_1` FOREIGN KEY (`id_user`) REFERENCES `users` (`email`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
