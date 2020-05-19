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
    <title>Hệ thống Điểm danh Sinh viên</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Source+Sans+Pro:300,300i,400,400i,500,500i,600,600i,700,700i&amp;subset=latin-ext">
    <script src="{!! asset('/assets/js/vendors/jquery-3.2.1.min.js') !!}"></script>
    <script src="{!! asset('/assets/js/require.min.js') !!}"></script>
    <script>
      requirejs.config({
          baseUrl: '.'
      });
    </script>
    <!-- Dashboard Core -->
    <link href="{!! asset('/assets/css/dashboard.css') !!}" rel="stylesheet" />
    <script src="{!! asset('/assets/js/dashboard.js') !!}"></script>
    <!-- Input Mask Plugin -->
    <script src="{!! asset('/assets/plugins/input-mask/plugin.js') !!}"></script>
    <link href="{!! asset('/assets/css/custom.css') !!}" rel="stylesheet" />
  </head>
  <body class="login">
    <div class="page">
        <div class="page-single">
        <div class="container">
          <div class="row">
            <div class="col col-login mx-auto">
              <form class="card" action="" method="post">
              <input type="hidden" name="_token" value="{{csrf_token()}}">
                <div class="card-body p-6">
                  <div class="card-title text-center">
                        <h1>Admin Login</h1>
                  </div>
                  <div class="form-group">
                    <label class="form-label">Username</label>
                    <input type="text" class="form-control" name='taikhoan' placeholder="Nhập Username">
                    <p class="text-danger">{{$errors->first('taikhoan')}}</p>
                  </div>
                  <div class="form-group">
                    <label class="form-label">
                      Password
                    </label>
                    <input type="password" class="form-control" name='matkhau' placeholder="Nhập Mật Khẩu">
                    <p class="text-danger">{{$errors->first('matkhau')}}</p>
                  </div>
                  <div class="form-footer">
                    <button type="submit" class="btn btn-primary btn-block">Đăng nhập</button>
                  </div>
                </div>
                @if(session()->has('errormessage'))
    <div class="alert alert-danger text-center">
        {{ session()->get('errormessage') }}
    </div>
@endif
              </form>
            </div>
          </div>
        </div>
      </div>
    </div>
  </body>
</html>