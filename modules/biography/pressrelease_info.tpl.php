<?php
// $Id$
/**
* Template to display biography nodes.
*
* Fields available:
* $dateline: cleaned plain text string
* $intro: cleaned HTML string
* $contact: cleaned HTML string
*/
?>

<div class="biography_info">
<h2><?php print t('Dateline');?>:</h2>
<?php print $dateline;?>
<h2><?php print t('Intro');?>:</h2>
<?php print $intro;?>
<h2><?php print t('Body');?>:</h2>
<?php print $body;?>
<h2><?php print t('Contacts');?>:</h2>
<?php print $contact;?>
</div>