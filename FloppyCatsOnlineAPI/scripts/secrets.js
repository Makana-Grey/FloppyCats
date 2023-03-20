import * as fs from 'fs'
import * as path from 'path'
import { fileURLToPath } from 'url'
import chalk from 'chalk'

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

const log = console.log

;(function restorThunderSecrets() {
    /*
        ~/secrets/secrets.json file structure: 
        {
            "prod": "..." //Here production api host name
        }
    */

    function writeSecrets(source, dest) {
        try {
            const prod = dest[0].data.filter((d) => d.name === 'prod')[0]
            prod.value = source.prod
        } catch (err) {
            log(chalk.red(err))
            return false
        }
        return true
    }

    log(chalk.yellow(`Start restoring thunder secrets`))

    const source = path.join(__dirname, '..', '..', 'secrets', 'secrets.json')
    const dest = './thunder-tests/thunderEnvironment.json'

    log(chalk.yellow(`Check exists secrets and destination files`))
    if (!fs.existsSync(source) || !fs.existsSync(dest)) {
        log(
            chalk.red(
                `Cant't restore secrets cause one of or both files is not existing`
            )
        )
        return
    }

    log(chalk.green(`Start secrets restoring`))

    let sourceData
    try {
        log(chalk.yellow(`Read thunder secrets file`))
        sourceData = fs.readFileSync(source, { encoding: 'utf8' })
        sourceData = JSON.parse(sourceData)
    } catch (err) {
        log(chalk.red(err))
        return
    }

    let destData
    try {
        log(chalk.yellow(`Read thunder destination file`))
        destData = fs.readFileSync(dest, { encoding: 'utf8' })
        destData = JSON.parse(destData)
    } catch (err) {
        log(chalk.red(err))
        return
    }

    log(chalk.yellow(`Write secrets to dest file`))
    if (!writeSecrets(sourceData, destData)) {
        log(chalk.red('Cant write secrets data'))
        return
    }

    log(chalk.yellow(`Start write new content to thunder file`))
    try {
        fs.writeFileSync(dest, JSON.stringify(destData), { flag: 'w' })
    } catch (err) {
        log(chalk.red(err))
    }

    log(chalk.green(`Thunder secrets succesfuly restored`))
})()
