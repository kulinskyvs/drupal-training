<?php

/**
 * Define drupal filter class 
 */
interface Filter {
  
  /**
   * Returns the name of the filter
   */
  public function getName();
  
  
  /**
   * Returns description of the filter
   */
  public function getDescription();
  
  
  /**
   * Returns filter's tip
   */
  public function getTip($long);
  
  /**
   * Prepare the given text 
   * @return prepared text 
   */
  public function prepare($text);
  
  /**
   * Process the given text and returns the transformed text 
   * 
   * @return transformed text
   */
  public function process($text);
  
  
  /**
   * Return HTML form controls for current filter 
   */
  public function settings();
}


////////////////////////////////////////////////////////////////////////////////
class PlaceHolderFilter implements Filter {
  private static $salutation_placeholder = '{{salutation}}';
  private static $briefname_placeholder = '{{brief name}}';
  
  private static $var_salutation = 'sitenews_salutation';
  private static $var_name = 'sitenews_name';
  
  public function getDescription() {
    return t('Replaces '.self::$salutation_placeholder.' with the news brief '.
             'salutation, and '.self::$briefname_placeholder.' with the news brief name.');
  }

  public function getName() {
   return t('News Brief Placeholders'); 
  }

  public function getTip($long) {
    $text = "Instances of ".self::$briefname_placeholder.
        " will be replaced by the global name for site news.".
        " ".self::$salutation_placeholder." will be replaced with the global  greeting message.";
    if ($long) {
    $text .= "Site News name and salutation text can be configured ".
        "from the administration interface.";  
      }
      return $text;
  }
  
  public function prepare($text) {
    //no preprocessing is required
    return $text;
  }

  public function process($text) {
    $text = str_replace(self::$salutation_placeholder, 
        variable_get(self::$var_salutation, 'Dear Site user'), $text);
    $text = str_replace(self::$briefname_placeholder,
       variable_get(self::$var_name, 'Site news'), $text);
    return $text;    
  }
  
  public function settings() {
    $form = array();
    
    $form['sitenews_filter'] = array(
      '#type' => 'fieldset',
      '#title' => t('Site News Filters'),
      '#collapsible' => true,
      '#collapsed' => false,
    );
    
    $form['sitenews_filter'][self::$var_salutation] = array(
      '#type' => 'textfield',
      '#description' => t('The greeting'),
      '#title' => t('Salutation'),
      '#default_value' => variable_get(self::$var_name, 'Dear Site User,'),
    );
    
    $form['sitenews_filter'][self::$var_name] = array(
      '#type' => 'textfield',
      '#description' => t('Title of the site news'),
      '#title' => t('Site News Name'),
      '#default_value' => variable_get(self::$var_name, 'Site News'),
    );
    
    return $form;    
  }
  
}


////////////////////////////////////////////////////////////////////////////////
class TaglessFilter implements Filter {
  public function getDescription() {
    return t('Removes all tags (HTML or XML elements).');
  }

  public function getName() {
    return t('Remove All HTML/XML Tags');
  }

  public function getTip($long) {
    return "HTML and XML tags will be removed from the final output.";
  }
  
  public function prepare($text) {
    //no preprocessing is required
    return $text;
  }

  public function process($text) {
    //just strip all the tags
    return strip_tags($text);
  }
  
  public function settings() {
    return array();
  }
}


////////////////////////////////////////////////////////////////////////////////
class UpperCaseFilter implements Filter {
  
  public function getDescription() {
    return t('Tranforms all the characters into upper case');
  }

  public function getName() {
    return t('Upper case filter');
  }

  public function getTip($long) {
    return "All the characters will be in upper case";
  }
  
  public function prepare($text) {
    //no preprocessing is required
    return $text;
  }

  public function process($text) {
    //just strip all the tags
    return strtoupper($text);
  }
  
  public function settings() {
    return array();
  }
}


////////////////////////////////////////////////////////////////////////////////
class FilterFactory  {
  
  private static $placeHolderFilter;
  private static $taglessFilter;
  private static $upperCaseFilter;
  
  
  /**
   * Returns filter by its delta
   * 
   * @param type $filterDelta 
   */
  public static function getFilterByDelta($filterDelta) {
    self::initFilter();
    switch ($filterDelta) {
      case NEWSBRIEF_PLACEHOLDER_FILTER_DELTA:
        return self::$placeHolderFilter;

      case NEWSBRIEF_TAGLESS_FILTER_DELTA:
        return self::$taglessFilter;
        
      case NEWSBRIEF_UPPER_FILTER_DELTA:
        return self::$upperCaseFilter;

      default:
        throw new Exception("Can't find filter with delta=" . $filterDelta);
    }
  }
  
  private static function initFilter() {
    if (!isset(self::$placeHolderFilter))
      self::$placeHolderFilter = new PlaceHolderFilter ();
    
    if (!isset(self::$taglessFilter))
      self::$taglessFilter = new TaglessFilter ();
    
    if (!isset(self::$upperCaseFilter))
      self::$upperCaseFilter = new UpperCaseFilter();
  }
}