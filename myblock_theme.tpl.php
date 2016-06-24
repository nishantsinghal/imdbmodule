<?php
$st='<div style="color:red">';
foreach($header as $fe){
	$st.=$fe;
}
$st.='</div>
<div style="color:blue">';
foreach($rows as $fe){
	$st.=$fe[0].'<br>';
}
$st.='</div>';
echo $st;
?>