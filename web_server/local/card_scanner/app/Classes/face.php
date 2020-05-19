<?php

use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Client;

namespace App\Classes;

class My_Face
{
    private $app_id = '0d71082b';
    private $key = '2e8d605f6cb25536340740cfeeed5043';
    private $gallery_name = 'MyGallery';
    private $client = '';

    public function __construct()
    {
        $this->client = new \GuzzleHttp\Client();
    }

    private function action(String $url, $data = array())
    {
        try {
            $res = $this->client->request('POST', $url, [
                'headers' => [
                    'Content-Type' => 'application/json',
                    'app_id' => $this->app_id,
                    'app_key' => $this->key,
                ],
                'json' => $data,
                ]);

            return json_decode($res->getBody());
        } catch (\Exception $e) {
        	dd($e);
            return false;
        }
    }

        public function listall()
    {

        $data = $this->action('https://api.kairos.com/gallery/list_all');
        
        return $data ?? '';
    }

    public function view()
    {
        $data = $this->action('https://api.kairos.com/gallery/view', ['gallery_name' => 'MyGallery']);

        return $data ?? '';
    }

    public function enroll($image, $label)
    {
        // to get base64
        // $image_data = base64_encode(file_get_contents($args["image_path"]));
        $image = base64_encode(file_get_contents($image));
        $data = $this->action('https://api.kairos.com/enroll',
        [
        'image' => $image,
        'subject_id' => $label,
        'gallery_name' => $this->gallery_name,
        ]
    );

        return $data ?? '';
    }

    public function recognize($image)
    {
        $image = base64_encode(file_get_contents($image));
        $data = $this->action('https://api.kairos.com/recognize',
        [
        'image' => $image,
        'gallery_name' => $this->gallery_name,
        ]
    );

        return $data ?? '';
    }

        public function delete_subject($id)
         {
        
        $data = $this->action('https://api.kairos.com/gallery/remove_subject',
        [
        
        'gallery_name' => $this->gallery_name,
        'subject_id' => $id
        ]
        );

        return $data ?? '';
    }



}
