-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 19, 2020 at 01:34 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.4.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `countstd`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `id` int(10) UNSIGNED NOT NULL,
  `taikhoan` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `diemdanhs`
--

CREATE TABLE `diemdanhs` (
  `masv` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `mamon` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `buoivang` date NOT NULL,
  `mathe` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `diemdanhs`
--

INSERT INTO `diemdanhs` (`masv`, `mamon`, `buoivang`, `mathe`, `created_at`, `updated_at`) VALUES
('B1509325', 'CN123-S5', '2019-05-27', NULL, NULL, NULL),
('B1509326', 'CN123-S5', '2019-05-27', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `lops`
--

CREATE TABLE `lops` (
  `id` int(10) UNSIGNED NOT NULL,
  `malop` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `tenlop` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `lops`
--

INSERT INTO `lops` (`id`, `malop`, `tenlop`, `created_at`, `updated_at`) VALUES
(1, 'CN123-S5', 'CN123-S5', NULL, NULL),
(2, 'CN123-C5', 'CN123-C5', NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `migrations`
--

CREATE TABLE `migrations` (
  `id` int(10) UNSIGNED NOT NULL,
  `migration` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `batch` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `migrations`
--

INSERT INTO `migrations` (`id`, `migration`, `batch`) VALUES
(1, '2014_10_12_000000_create_users_table', 1),
(2, '2014_10_12_100000_create_password_resets_table', 1),
(3, '2018_06_11_033157_create_lops_table', 1),
(4, '2018_06_11_033327_create_sinh_viens_table', 1),
(5, '2018_06_11_035258_create_monhocs_table', 1),
(6, '2018_06_11_040318_create_diemdanhs_table', 1),
(7, '2018_06_11_095021_create_admin_table', 1);

-- --------------------------------------------------------

--
-- Table structure for table `monhocs`
--

CREATE TABLE `monhocs` (
  `id` int(10) UNSIGNED NOT NULL,
  `mamon` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `tenmon` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `sotinchi` int(11) NOT NULL,
  `sotiet` int(11) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `monhocs`
--

INSERT INTO `monhocs` (`id`, `mamon`, `tenmon`, `sotinchi`, `sotiet`, `created_at`, `updated_at`) VALUES
(1, 'CN123-S5', 'CN123-S5', 3, 45, NULL, NULL),
(2, 'CN123-C5', 'CN123-C5', 3, 45, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `password_resets`
--

CREATE TABLE `password_resets` (
  `email` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `token` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `sinh_viens`
--

CREATE TABLE `sinh_viens` (
  `id` int(10) UNSIGNED NOT NULL,
  `masv` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `hoten` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `gioitinh` varchar(3) COLLATE utf8mb4_unicode_ci NOT NULL,
  `malop` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `sinh_viens`
--

INSERT INTO `sinh_viens` (`id`, `masv`, `hoten`, `gioitinh`, `malop`, `created_at`, `updated_at`) VALUES
(1, 'B1509325', 'Lê Ngọc Oanh', 'Nam', 'CN123-S5', '2019-05-27 00:15:17', '2019-05-27 00:15:17'),
(2, 'B1509326', 'Nguyễn Tuấn Khanh', 'Nữ', 'CN123-S5', '2019-05-27 00:15:17', '2019-05-27 00:15:17');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `admin_taikhoan_unique` (`taikhoan`);

--
-- Indexes for table `diemdanhs`
--
ALTER TABLE `diemdanhs`
  ADD PRIMARY KEY (`masv`,`mamon`,`buoivang`),
  ADD KEY `diemdanhs_mamon_foreign` (`mamon`);

--
-- Indexes for table `lops`
--
ALTER TABLE `lops`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `lops_malop_unique` (`malop`);

--
-- Indexes for table `migrations`
--
ALTER TABLE `migrations`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `monhocs`
--
ALTER TABLE `monhocs`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `monhocs_mamon_unique` (`mamon`);

--
-- Indexes for table `password_resets`
--
ALTER TABLE `password_resets`
  ADD KEY `password_resets_email_index` (`email`);

--
-- Indexes for table `sinh_viens`
--
ALTER TABLE `sinh_viens`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `sinh_viens_masv_unique` (`masv`),
  ADD KEY `sinh_viens_malop_foreign` (`malop`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `users_email_unique` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `lops`
--
ALTER TABLE `lops`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `migrations`
--
ALTER TABLE `migrations`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `monhocs`
--
ALTER TABLE `monhocs`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `sinh_viens`
--
ALTER TABLE `sinh_viens`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `diemdanhs`
--
ALTER TABLE `diemdanhs`
  ADD CONSTRAINT `diemdanhs_mamon_foreign` FOREIGN KEY (`mamon`) REFERENCES `monhocs` (`mamon`) ON DELETE CASCADE,
  ADD CONSTRAINT `diemdanhs_masv_foreign` FOREIGN KEY (`masv`) REFERENCES `sinh_viens` (`masv`) ON DELETE CASCADE;

--
-- Constraints for table `sinh_viens`
--
ALTER TABLE `sinh_viens`
  ADD CONSTRAINT `sinh_viens_malop_foreign` FOREIGN KEY (`malop`) REFERENCES `lops` (`malop`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
