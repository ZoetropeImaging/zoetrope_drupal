<?php

function zoetrope_viewer_migrate_api() {
  $api = array(
    'api' => 2,
    'field handlers' => array('ZoetropeUUIDFieldHandler')
  );
  return $api;
}

class ZoetropeUUIDFieldHandler extends MigrateFieldHandler {
  public function __construct() {
    $this->registerTypes(array('zoetrope_uuid_field'));
  }

  static function arguments($zoetrope_uuid = NULL, $start_position = NULL) {
    $arguments = array();
    if (!is_null($zoetrope_uuid)) {
      $arguments['zoetrope_uuid'] = $zoetrope_uuid;
    }
    if (!is_null($start_position)) {
      $arguments['start_position'] = $start_position;
    }
    return $arguments;
  }

  /**
   * Implementation of MigrateFieldHandler::fields().
   *
   * @param $type
   *  The field type.
   * @param $instance
   *  Instance info for the field.
   * @param Migration $migration
   *  The migration context for the parent field. We can look at the mappings
   *  and determine which subfields are relevant.
   * @return array
   */
  public function fields($type, $instance, $migration = NULL) {
    $fields = array();
    if ($type == 'zoetrope_uuid_field') {
      $fields['start_position'] = t('Subfield: the starting position');
      $fields['gallery_image_positions'] = t('Subfield: the gallery image positions');
    }
    return $fields;
  }

  public function prepare($entity, array $field_info, array $instance, array $values) {
    if (isset($values['arguments'])) {
      $arguments = $values['arguments'];
      unset($values['arguments']);
    }
    else {
      $arguments = array();
    }

    $migration = Migration::currentMigration();
    $destination = $migration->getDestination();

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      $item = array();

      $item['zoetrope_uuid'] = $value;

      if (isset($arguments['start_position'])) {
        if (is_array($arguments['start_position'])) {
          $item['start_position'] = intval($arguments['start_position'][$delta]);
        }
        else {
          $item['start_position'] = intval($arguments['start_position']);
        }
      }

      /* Will be a list<struct> with keys "weight" and "position". "postition" is required, "weight" is optional. */
      if (isset($arguments['gallery_image_positions']) && is_array($arguments['gallery_image_positions'])) {
        
        if(is_array(reset(reset($arguments['gallery_image_positions'])))){
          $item['gallery_image_positions'] = _zoetrope_viewer_gallery_image_helper($arguments['gallery_image_positions'][$delta]);
        }
        else {
          $item['gallery_image_positions'] = _zoetrope_viewer_gallery_image_helper($arguments['gallery_image_positions']);
        }
      }

      $return[LANGUAGE_NONE][] = $item;
      $delta++;
    }
    return isset($return) ? $return : NULL;
  }
}

function _zoetrope_viewer_gallery_image_helper($list){
  $ret = array();
  foreach ($list as $struct) {
    if(is_array($struct) && isset($struct['position']) && is_numeric($struct['position'])){
      $ret[] = array(
        'position' => intval($struct['position']),
        'weight' => (isset($struct['weight'])? floatval($struct['weight']) : 0),
      );
    }
  }
  return $ret;
}