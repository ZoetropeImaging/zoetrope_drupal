Zoetrope Viewer Module

-- SUMMARY --

The Zoetrope viewer module provides fields, field formatters and tokens for the zoetrope viewer.


-- REQUIREMENTS --

None.

-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.

-- CONFIGURATION --

Add a `Zoetrope ID` field to an entity, using the `Zoetrope Engage Viewer` as the display type.

-- DISPLAY FORMATTERS --

Zoetrope images are always square, though the size is configurable, using standard image styles. Image styles are not actually processed for Zoetrope images - only the sizes are honored. Any changes to the image styling need to be done with CSS or by using an alternate trigger image.

If you want to combine a list of regular images with Zoetrope images for display, an image formatter `Image + Zoetrope Images` is provided to merge a Zoetrope ID field into an image field for display.

-- TOKENS --

The main use case for the tokens in this module is to use them in conjunction with the metatags module.

Provided Tokens:
*. [`entity:field_name`] - The 500px preview image url