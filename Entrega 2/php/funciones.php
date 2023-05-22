<?php


//user functions


function check_user_failed_attempts($DB_conn, $user){

  $failed_attempts_query = mysqli_query($DB_conn, "SELECT failed_attempts FROM benja_usuarios WHERE username = '". $user ."'" );
  $failed_attempts_query_row = mysqli_fetch_array($failed_attempts_query);

  return $failed_attempts_query_row['failed_attempts'];
  
}

//timer functions

function check_bloqued_user_timeout($DB_conn, $user){
  $end_time_query = mysqli_query($DB_conn, "SELECT time_when_unblock FROM benja_usuarios WHERE username = '". $user ."'");
  $end_time_query_row = mysqli_fetch_array($end_time_query);

  return $end_time_query_row['time_when_unblock'];
}

function set_bloqued_user_timeout($timer_duration_secs, $DB_conn, $user)
{
  $end_time = check_bloqued_user_timeout($DB_conn, $user);

  if($end_time == 0){
    
    $end_time = time() + $timer_duration_secs;
    mysqli_query($DB_conn, "UPDATE benja_usuarios SET time_when_unblock = '$end_time' WHERE username = '". $user ."'");

  }
  
}

function unblock_user($DB_conn, $user){

  mysqli_query($DB_conn, "UPDATE benja_usuarios SET failed_attempts = 0 WHERE username = '". $user ."'"); // failed_attempts reset
  mysqli_query($DB_conn, "UPDATE benja_usuarios SET time_when_unblock = 0 WHERE username = '". $user ."'" ); // time_when_unblock reset

}

function bloqued_user_timeout($DB_conn, $user){

  $end_time = check_bloqued_user_timeout($DB_conn, $user);

  $time_left = $end_time - time();
  $time_formatted = gmdate("i:s", $time_left);

  if(time() < $end_time){

    echo "El ingreso de credenciales esta bloqueado por favor espere " .$time_formatted. " minutos";

  }
  else{
    echo "El ingreso de credenciales esta bloqueado por favor espere unos instantes";
    unblock_user($DB_conn, $user);
  }
  
}

?>