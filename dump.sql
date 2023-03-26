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
('pidonematteo@hotmail.it', '2023-03-27', '2', ''),
('pidonematteo@hotmail.it', '2023-03-28', '1', ''),
('pidonematteo@hotmail.it', '2023-03-29', '1', ''),
('pidonematteo@hotmail.it', '2023-03-30', '0', ''),
('pidonematteo@hotmail.it', '2023-03-31', '2', 'Mi secco a lavorare'),
('pidonematteo@hotmail.it', '2023-04-07', '0', ''),
('pidonematteo@hotmail.it', '2023-04-13', '0', ''),
('pidonematteo@hotmail.it', '2023-04-14', '0', '');

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
('pidonematteo2@hotmail.it', 'pippopluto', 'prova', 'prova', 'Programmatore informatico a tempo pieno presso TommiPri SrL', '0'),
('pidonematteo@hotmail.it', 'prova', 'Matteo', 'Pidone', 'Programmatore informatico a tempo pieno presso TommiPri SrL', '0'),
('pippo@pippo.it', 'poroew', 'Papero', 'Paperin', 'Programmatore informatico a tempo pieno presso TommiPri SrL', '0'),
('prova@test.it', 'prova', 'Matteo', 'Pidone', 'Programmatore informatico a tempo pieno presso TommiPri SrL', '1');

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
