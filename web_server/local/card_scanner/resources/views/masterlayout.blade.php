<!doctype html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <meta http-equiv="Content-Language" content="en" />
    <meta name="msapplication-TileColor" content="#2d89ef">
    <meta name="theme-color" content="#4188c9">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent"/>
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="mobile-web-app-capable" content="yes">
    <meta name="HandheldFriendly" content="True">
    <meta name="MobileOptimized" content="320">
    <link rel="shortcut icon" type="image/x-icon" href="./favicon.ico" />
    <title>New Điểm Danh</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Source+Sans+Pro:300,300i,400,400i,500,500i,600,600i,700,700i&amp;subset=latin-ext">
    <script src="{!! asset('assets/js/vendors/jquery-3.2.1.min.js') !!}"></script>
    <script src="{!! asset('assets/js/vendors/bootstrap.bundle.min.js') !!}"></script>
    <link href="{!! asset('/assets/css/tabler.css') !!}" rel="stylesheet" />
    <script src="{!! asset('../assets/js/dropzone.js') !!}"></script>
    <link href="{!! asset('/assets/css/fileinput.min.css') !!}" rel="stylesheet" />
    <script src="{!! asset('../assets/js/fileinput.min.js') !!}"></script> 
    <!-- <script src="{!! asset('../assets/js/require.min.js') !!}"></script> -->
    
    <!-- Dashboard Core -->
    <link href="{!! asset('/assets/css/dashboard.css') !!}" rel="stylesheet" />
    <link href="{!! asset('/assets/css/dropzone.css') !!}" rel="stylesheet" />
    <!-- <script src="{!! asset('/assets/js/dashboard.js') !!}"></script> -->
    <link href="{!! asset('/assets/css/custom.css') !!}" rel="stylesheet" />
  
    
  </head>
  <body>
  @include('header')
    <div class="d-flex">
        @include('sidebar')
        @yield('content')
    </div>
  </body>
  <script type="text/javascript">
    
      $(document).ready(function () {
         $('#sidebarCollapse').on('click', function () {
             $('#sidebar').toggleClass('active');
         });
     });

     
     
 </script>
</html>