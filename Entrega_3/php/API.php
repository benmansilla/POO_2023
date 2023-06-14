<?php

include("./funciones.php");
require_once("./db.php");


// Verificación de que las variables iniciales este seteadas

if (isset($_GET['user']) && isset($_GET['pass'])) {
  $user = $_GET['user'];
  $pass = $_GET['pass'];

  if (isset($_GET['l_search'])) {
    $latest_search = $_GET['l_search'];
  }

}

if (isset($user) && isset($pass)) {
  $login_query = mysqli_query($DB_conn, "SELECT name, surname FROM benja_usuarios WHERE password='" . $pass . "' and username='" . $user . "'");
  $num_row = mysqli_num_rows($login_query);
  $failed_attempts = check_user_failed_attempts($DB_conn, $user);

  if ($failed_attempts == 3) {
    set_bloqued_user_timeout(300, $DB_conn, $user);
    bloqued_user_timeout($DB_conn, $user);
  } else {
    if ($num_row > 0) {
      mysqli_query($DB_conn, "UPDATE benja_usuarios SET failed_attempts = 0 WHERE username = '" . $user . "'");
      $login_query_row = mysqli_fetch_array($login_query);

      if (isset($latest_search)) {
        $latest_search_query = mysqli_query($DB_conn, "UPDATE benja_usuarios SET latest_search = '". $latest_search ."' WHERE username = '" . $user . "'");
      }

      $latest_search_get_query = mysqli_query($DB_conn, "SELECT latest_search FROM benja_usuarios WHERE username = '" . $user ."'");
      $latest_search_get_query_row = mysqli_fetch_array($latest_search_get_query);

      if(!empty($latest_search_get_query_row)){
        echo "Bienvenido/a " . $login_query_row['name'] . " " . $login_query_row['surname'] . "." . $latest_search_get_query_row['latest_search'];
      }
    } else {
      echo "Nombre de usuario y/o contrasenia incorrectas";
      ++$failed_attempts;
      mysqli_query($DB_conn, "UPDATE benja_usuarios SET failed_attempts = '$failed_attempts' WHERE username = '" . $user . "'");

    }

  }

}

?>