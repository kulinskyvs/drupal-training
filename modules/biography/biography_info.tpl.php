<?php
// $Id$
/**
* Template to display biography nodes.
*
* Fields available:
* $body: cleaned plain body text 
* $dates: cleaned plain text string
* $life: cleaned HTML string
* $works: cleaned HTML string
*/
?>

<div class="biography_info">
<h2><?php print t('Dates');?>:</h2>
<?php print $dates;?>
<h2><?php print t('Life');?>:</h2>
<?php print $life;?>
<h2><?php print t('Works');?>:</h2>
<?php print $works;?>
</div>