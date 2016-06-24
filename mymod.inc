<?php
/**
* all extra functions of mymod
**/

function mymod_form($form,&$form_state) {
	$form['first_name'] = array(
   '#type'=>'textfield',
   '#title'=>t('First Name'),
   '#required' => TRUE, 
   );
  $form['last_name'] = array(
   '#type'=>'textfield',
   '#title'=>t('Last Name'),
   '#required' => TRUE, 
   );
  $form['pass'] = array(
    '#type' => 'password', 
    '#title' => t('Password'), 
    '#maxlength' => 64, 
    '#size' => 15,
    );
  $form['submit_button'] = array(
	 '#type' => 'submit','#value' => t('Save'),	
	);
	return $form;
 }

 function mymod_form_validate($form, &$form_state) {
 }

 function mymod_form_submit($form, &$form_state) {
  $fname = $form_state['values']['first_name'];
  $lname = $form_state['values']['last_name'];
  $pass  = $form_state['values']['pass'];
  // $result = db_insert('mymod_form')
  //   ->fields(array(
  //       'fname' => $fname,
  //       'lname' => $lname,
  //       'password' => $pass,
  //   ))
  //   ->execute();
  //   if ($result){
  //       drupal_set_message('data saved successfully.');
  $query = "INSERT INTO {mymod_form} (fname,lname,password) VALUES ('$fname', '$lname', '$pass')";
    $result = db_query($query);
  if ($result !== FALSE){
    drupal_set_message('data saved successfully.');
  }
 }



 function mymod_form_show($data) {
  $query = "SELECT * FROM {mymod_form} where fname like '%$data%'";
  $result = db_query($query);
  $rows = array();
  $i = 0;
//   while ($rs = db_fetch_object($result)) {
//    $rows[$i]['fname'] = $rs['fname'];
//    $rows[$i]['lname'] = $rs['lname'];
//    $rows[$i]['pass'] = $rs['password'];
//    $i++; 
//   }
 $header = array(t('First name.'), t('Last Name'), t('Password'));
//   return theme('table', $header, $rows);
   
 foreach ($result as $key => $value) {
   $row = array();
    $row[] = $value->fname;
    $row[] = $value->lname;
    $row[] = $value->password;
    //....etc, the rest of the fields
    $rows[] = $row;
  }
  //   while ($data = db_fetch_object($result)){

 // return "hi";
  //dpm($rows);
  return theme('table', array('header' => $header, 'rows' => $rows));
}

  function mymod_form_filtershow($form,&$form_state) {
    $form['first_name'] = array(
     '#type'=>'textfield',
     '#title'=>t('First Name filter'), 
     ); 

    $form['submit_button'] = array(
     '#type' => 'submit',
     '#value' => t('Search'), 
    );
    //$fname = $form_state['input']['first_name'];
    //variable_set('fname',$fname);
    //$show = mymod_form_show($fname);
    //dpm($fname);
    //$GLOBALS['z'] = $fname;
    //dpm($GLOBALS['z']);
    //dpm($form_state);///
    //$view = array('frm'=>$form,'fname'=>$fname);
    return $form;
  }

  function mymod_form_filtershow_submit($form,&$form_state) {
    $fname = $form_state['values']['first_name'];
    // dpm($fname);
    // dpm($form_state); 
    drupal_goto("examples/form-show", array(
    'query' => array(
        'firstname' => $fname,
    ),
    ));
  }

  function filtershow($form) {
    //print_r($filter);
    // $fname = $filter['fname'];
    // $form1 = $filter['frm'];
    // dpm($filter);
    // dpm($fname);
    //dpm($GLOBALS['z']);
    //if(isset($form_state['values']['submit_button']) && !empty($form_state['values']['submit_button'])) {
    //$fname = variable_get('fname');
    //dpm($fname);

    $view  = render(drupal_get_form($form));
    $fname = $_GET['firstname'];
    $view .= mymod_form_show($fname);
    //dpm($form);
    //dpm($form_state);
  //  }
    return $view;
  }

  function myblock_view() {
    $query  = "Select lname from {mymod_form}";
    $result = db_query($query);
    $rows = array();
    $header = array(t('Last Name'));
//   return theme('table', $header, $rows);
   
    foreach ($result as $key => $value) {
    $row = array();
    $row[] = $value->lname;
    $row[] = $value->password;
    //....etc, the rest of the fields
    $rows[] = $row;
  } 
  //dpm($rows);
   return theme('table1', array('header' => $header, 'rows' => $rows));
  }