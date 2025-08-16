import os
import platform

CONSTRAINTS = [
    (
        ['cver', 'iso'],
        ['test', 'threads', 'on']
    )
]

def fixture_dir():
    return os.path.join('Unity', 'extras', 'fixture')

def memory_dir():
    return os.path.join('Unity', 'extras', 'memory')

def add_rules(olvars):
    rule = olvars.rule(olvars.slashify('$(test_BLDDIR)', 'reports.d', 'coverage.d'))
    dep = olvars.slashify('$(test_BLDDIR)', 'reports.d', 'coverage.info')
    tmp = ''

    rule.normal_depend(dep)
    if platform == 'win32':
        rule.step('$(call MKDIR, $@)')
    else:
        rule.step('genhtml ' + dep + ' --show-details --output-directory $@')

    rule = olvars.rule(olvars.slashify('$(test_BLDDIR)', 'reports.d', 'coverage.info'))
    dep = olvars.slashify('$(test_BLDDIR)', 'reports.d', 'valgrind.info')
    rule.normal_depend(dep)
    if platform == 'win32':
        rule.step('echo No coverage for Windows. > $@')
    else:
        rule.step('lcov --capture --directory ./ --output-file $@')

    rule = olvars.rule(olvars.slashify('$(test_BLDDIR)', 'reports.d', 'valgrind.info'))
    dep = olvars.slashify('$(test_BLDDIR)', 'app')
    rule.normal_depend(dep)
    dep = olvars.slashify('$(test_BLDDIR)', 'reports.d')
    rule.order_depend(dep)
    if platform == 'win32':
        rule.step(olvars.slashify('.', '$(test_BLDDIR)', 'app'))
        rule.step('echo No memchecks for Windows. > $@')
    else:
        tmp = 'valgrind --leak-check=full --show-leak-kinds=all '
        tmp = tmp + '--track-origins=yes --error-exitcode=1 --log-file="$@" '
        tmp = tmp + olvars.slashify('.', '$(test_BLDDIR)', 'app')
        rule.step(tmp)

def join(olvars):
    settings = olvars.settings()

    if settings['cver'] == 'gnu':
        olvars.append('test_CFLAGS', '-std=gnu11')
    elif settings['cver'] == 'iso':
        olvars.append('test_CFLAGS', '-std=c99')
        olvars.append('test_CFLAGS', '-pedantic')
    else:
        olvars.fail('Unknown cver: ' + settings['cver'] + '.')

    if settings['test']['threads'] == 'on':
        olvars.append('test_CFLAGS', '-DTHREADS_EN=1')
    elif settings['test']['threads'] == 'off':
        olvars.append('test_CFLAGS', '-DTHREADS_EN=0')
    else:
        node.fail('Unknown threads mode: ' + settings['test']['threads'] + '.')

    olvars.append('unity_DIR', 'Unity')
    olvars.append('unity_INCS', '-I' + olvars.slashify('Unity', 'src'))
    olvars.append('unity_INCS', '-I' + olvars.slashify(fixture_dir(), 'src'))
    olvars.append('unity_INCS', '-I' + olvars.slashify(memory_dir(), 'src'))
    olvars.append('unity_OBJS', olvars.slashify('Unity', 'src', 'unity.o'))
    olvars.append(
        'unity_OBJS',
        olvars.slashify(fixture_dir(), 'src', 'unity_fixture.o'))
    olvars.append(
        'unity_OBJS',
        olvars.slashify(memory_dir(), 'src', 'unity_memory.o'))
    olvars.append('test_DIR', olvars.slashify(olvars.acwd()))
    olvars.append('test_BLDDIR', olvars.cwd())
    olvars.append('test_OBJS', olvars.slashify(olvars.cwd(), 'main.o'))
    olvars.include('extra')
    add_rules(olvars)
