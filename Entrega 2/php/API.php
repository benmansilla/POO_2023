<?php

include("./funciones.php");
require_once("./db.php");

if ( isset( $_GET[ 'user' ] ) ) {


  $user = $_GET[ 'user' ];
  
  $pass = $_GET[ 'pass' ];
}

$login_query = mysqli_query($DB_conn, "SELECT name, surname FROM benja_usuarios WHERE password='" . $pass . "' and username='" . $user . "'" );
$num_row = mysqli_num_rows( $login_query);
$failed_attempts = check_user_failed_attempts($DB_conn, $user);

if($failed_attempts == 3){
  set_bloqued_user_timeout(300, $DB_conn, $user);
  bloqued_user_timeout($DB_conn, $user);
}
else{

  if ( $num_row > 0) {

    echo "Acceso concedido";
    mysqli_query($DB_conn, "UPDATE benja_usuarios SET failed_attempts = 0 WHERE username = '". $user ."'" );
    //$login_query_row = mysqli_fetch_array($login_query);
    //echo "Bienvenido/a " .$login_query_row['name']. " " .$login_query_row['surname']. "\n";
    
    }
    else {
    
    echo "Nombre de usuario y/o contrasenia incorrectas";
    ++$failed_attempts;
    mysqli_query($DB_conn, "UPDATE benja_usuarios SET failed_attempts = '$failed_attempts' WHERE username = '". $user ."'" );
    
    }

}

?>