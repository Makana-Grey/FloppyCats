import * as fs from 'fs'
import chalk from 'chalk'

const log = console.log

;(function clearThunderEnvs() {
    function getThunderSecrets(data) {
        return data[0].data.filter((d) => d.name === 'prod')
    }

    function clearSecrets(secrets) {
        secrets.forEach((secret) => {
            secret.value = ''
        })
    }

    log(chalk.yellow(`Start clear thunder secrets task`))
    const path = './thunder-tests/thunderEnvironment.json'

    log(chalk.yellow(`Check exists ${path} file`))
    if (!fs.existsSync(path)) {
        log(chalk.green(`No file ${path}.`, 'Stop task and exit.'))
        return
    }

    log(
        chalk.green(
            `File ${path} is exist. Start clear thunder secrets in file`
        )
    )

    let jsonStr
    try {
        jsonStr = fs.readFileSync(path, { encoding: 'utf8' })
    } catch (err) {
        log(chalk.red(err))
        return
    }

    let data
    try {
        log(chalk.yellow(`Try parse file content to JSON object`))
        data = JSON.parse(jsonStr)

        const secrets = getThunderSecrets(data)

        if (!secrets.length) {
            log(chalk.green('No finded thunder secrets. Stop task.'))
            return
        }

        clearSecrets(secrets)
        log(chalk.green('Success to clear file secrets'))
    } catch (err) {
        log(
            chalk.red(
                'Error when parse JSON of file and clear thunder secrets',
                err
            )
        )
    }

    log(chalk.yellow(`Start write new content to thunder file`))
    try {
        fs.writeFileSync(path, JSON.stringify(data), { flag: 'w' })
    } catch (err) {
        log(chalk.red(err))
    }

    log(chalk.green(`Thunder secrets are cleared`))
})()
