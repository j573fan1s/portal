<?php
// $Id: uploadfield_file.inc,v 1.1.2.5 2009/12/23 13:46:09 heshanmw Exp $

/**
 * @file
 * hook_file and uploadfield file functions.
 */

/**
 * Implementation of hook_file_insert().
 */
function uploadfield_file_insert($file) {
// Currently empty. Thumbnails are now generated on preview.
}

/**
 * Implementation of hook_file_delete().
 *
 * Delete the admin thumbnail when the original is deleted.
 */
function uploadfield_file_delete($file) {
// delete thumb from files
//  file_set_status($file->data['video_thumb_fid'], FILE_STATUS_TEMPORARY);
  db_query('DELETE FROM {files} WHERE fid = %d', $file->data['video_thumb_fid']);

  // delete thums directory
  $thumbs_path = variable_get('video_thumb_path', 'video_thumbs');
  //files will save in files/video_thumbs/#fileId folder
  $tmp = file_directory_path(). '/' . $thumbs_path . '/' . $file->fid . '/';
  //  rmdir($tmp);
  _file_delete_tree($tmp);
//  if(@rmdir($tmp)) {
//  }
}


// delete dir and its content
function _file_delete_tree($current_dir) {
  if($dir = @opendir($current_dir)) {
    while (($f = readdir($dir)) !== false) {
      if($f > '0' and filetype($current_dir.$f) == "file") {
        file_delete($current_dir.$f);
      } elseif($f > '0' and filetype($current_dir.$f) == "dir") {
        _file_delete_tree($current_dir.$f."\\");
      }
    }
    closedir($dir);
    rmdir($current_dir);
  }
}

/**
 * Simple utility function to check if a file is an image.
 */
function uploadfield_file_is_image($file) {
  return TRUE;
  //TODO : add file validations
  $file = (object)$file;
  return in_array($file->filemime, array('image/jpg', 'image/pjpeg', 'image/jpeg', 'image/png', 'image/gif'));
}

/**
 * Given a file, return the path the image thumbnail used while editing.
 */
function uploadfield_file_admin_thumb_path($file, $create_thumb = TRUE) {
  $file = (object)$file;
  $short_path = preg_replace('/^' . preg_quote(file_directory_path(), '/') . '/', '', $file->filepath);
  $filepath = file_directory_path() . '/video_thumb' . $short_path;

  if ($create_thumb) {
    uploadfield_create_admin_thumb($file->filepath, $filepath);
  }

  return $filepath;
}

/**
 * Create a thumbnail to be shown while editing an image.
 */
function uploadfield_create_admin_thumb($source, $destination) {
  if (!is_file($source)) {
    return FALSE;
  }

  $info = image_get_info($source);
  $size = explode('x', variable_get('uploadfield_thumb_size', '100x100'));

  // Check if the destination image needs to be regenerated to match a new size.
  if (is_file($destination)) {
    $thumb_info = image_get_info($destination);
    if ($thumb_info['width'] != $size[0] && $thumb_info['height'] != $size[1] && ($info['width'] > $size[0] || $info['height'] > $size[1])) {
      unlink($destination);
    }
    else {
      return;
    }
  }

  // Ensure the destination directory exists and is writable.
  $directories = explode('/', $destination);
  array_pop($directories); // Remove the file itself.
  // Get the file system directory.
  $file_system = file_directory_path();
  foreach ($directories as $directory) {
    $full_path = isset($full_path) ? $full_path . '/' . $directory : $directory;
    // Don't check directories outside the file system path.
    if (strpos($full_path, $file_system) === 0) {
      field_file_check_directory($full_path, FILE_CREATE_DIRECTORY);
    }
  }

  // Create the thumbnail.
  if ($info['width'] <= $size[0] && $info['height'] <= $size[1]) {
    file_copy($source, $destination);
  }
  elseif (image_get_toolkit() && @image_scale($source, $destination, $size[0], $size[1])) {
  // Set permissions. This is done for us when using file_copy().
    @chmod($destination, 0664);
  }
  else {
    drupal_set_message(t('An image thumbnail was not able to be created.'), 'error');
  }
}
