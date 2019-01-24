load('//:buckaroo_macros.bzl', 'buckaroo_deps')
load('//:subdir_glob.bzl', 'subdir_glob')
load('//:extract.bzl', 'extract')

configure_options = read_config('configure', 'options', '')

genrule(
  name = 'configure',
  out = 'out',
  srcs = glob([
    'configure',
    '*.ac',
    '*.m4',
    '*.in',
    '*.sed',
    '*.spec',
    'bins/*.in',
    'docs/*.in',
    'uses/*',
    'zzip/*.in',
    'zzip/*.sed',
    'SDL/*.in',
  ]),
  cmd = ' && '.join([
    'cp -r $SRCDIR/. $TMP',
    'cp -r $(location //test:config)/. $TMP/test',
    'cp -r $(location //zzipwrap:config)/. $TMP/zzipwrap',
    'mkdir -p $OUT',
    'cd $OUT && $TMP/configure --silent --srcdir=$TMP ' + configure_options,
  ]),
)

cxx_library(
  name = 'zzip',
  header_namespace = '',
  exported_headers = dict(
    subdir_glob([
      ('', 'zzip/**/*.h'),
    ]).items() + [
      ('zzip/_config.h', extract(':configure', 'zzip/_config.h')),
    ]
  ),
  srcs = glob([
    'zzip/*.c',
  ]),
  deps = buckaroo_deps(),
  visibility = [
    'PUBLIC',
  ],
)
