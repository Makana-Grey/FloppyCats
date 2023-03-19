import { names } from '../data/names.js'
import { animals } from '../data/animals.js'
import { colors } from '../data/colors.js'

function rand(min, max) {
    return Math.floor(Math.random() * (max - min) + min)
}

/**
 * @returns {String} unique name
 */
export function generateName() {
    const color = colors[rand(0, colors.length)]
    const animal = animals[rand(0, animals.length)]

    let newName = color + '-' + animal

    const existedName = names.data.find(({ name }) => name === newName)

    if (existedName) {
        existedName.sequenceNumber++
        newName += '-' + existedName.sequenceNumber
    } else {
        names.data.push({ name: newName, sequenceNumber: 0 })
    }

    return newName
}
