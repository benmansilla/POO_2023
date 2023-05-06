<?php

require_once 'db.php';

if ( isset( $_GET[ 'user' ] ) ) {

$user = $_GET[ 'user' ];

$pass = $_GET[ 'pass' ];


$query = mysqli_query( $DB_conn, "SELECT name, surname FROM benja_usuarios WHERE password='" . $pass . "' and username='" . $user . "'" );

//$query = mysqli_query( $DB_conn, "SELECT name, surname FROM login" );

$row = mysqli_fetch_array( $query );


$num_row = mysqli_num_rows( $query );


if ( $num_row > 0 ) {

print( "Acceso OK!" );



}

else {

print( "Nombre de usuario y/0 contraseña incorrectas" );

}

}



?>