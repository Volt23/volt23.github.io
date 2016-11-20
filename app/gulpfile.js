var gulp = require('gulp');
var sass = require('gulp-sass');
var pug=require('gulp-pug');
var browserSync = require('browser-sync').create();

gulp.task('browserSync', function() {
  browserSync.init({
    server: {
      baseDir: '../'
    },
  })
})

// Gulp Sass Task 
gulp.task('sass', function() {
   return gulp.src('scss/**/*.scss')
   .pipe(sass({
      includePaths: [
        './bower_components',
      ],
    }))
  .pipe(sass().on('error', sass.logError))
  .pipe(gulp.dest('../css'));
})

gulp.task('pug',function(){
    return gulp.src(['pug/*.pug','!pug/**/_*.pug'])
    .pipe(pug({
      pretty: true
    }))
    .pipe(gulp.dest('../'))
});


// Watch scss folder for changes
gulp.task('watch',['sass','pug','browserSync'], function() {
  // Watches the scss folder for all .scss and .sass files
  // If any file changes, run the sass task
  gulp.watch('scss/*.scss', ['sass'])
  gulp.watch('pug/*.pug', ['pug'])
  gulp.watch('../*.html', browserSync.reload); 
  gulp.watch('../css/*.css', browserSync.reload); 
})


