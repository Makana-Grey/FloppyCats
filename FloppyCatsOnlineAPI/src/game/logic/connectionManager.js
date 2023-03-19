import { Player, players } from '../data/players.js'
import {
    isValidToConnect,
    isValidToRefresh,
} from '../validators/connectionValidators.js'
import { generateToken } from './tokenGenerator.js'
import { generateName } from './nameGenerator.js'
import { getPlayer } from './playerGetter.js'

/**
 * Object for refresh connection
 * @typedef {Object} Connector
 * @property {String} token
 * @property {String} ip
 * @property {Number} port
 */

/**
 * @param {Player} player
 * @returns {String | undefined}
 */
export function connect(player) {
    try {
        if (isValidToConnect(player)) {
            const name = generateName()
            const token = generateToken(name)

            const newPlayer = {
                ...player,
                name,
                token,
                isPublic: false,
                isPlay: false,
                connectionDate: new Date(),
            }
            players.data.push(newPlayer)

            return { name, token }
        }
    } catch (e) {
        console.log(e)
    }
    return undefined
}

/**
 * @param {Connector} connector
 * @returns {Boolean}
 */
export function refresh(connector) {
    try {
        if (isValidToRefresh(connector)) {
            const player = getPlayer(connector)

            if (player) {
                player.ip = connector.ip
                player.port = connector.port
                player.connectionDate = new Date()

                return true
            }
        }
    } catch (e) {
        console.log(e)
    } finally {
        updateConnections()
    }
    return false
}

function updateConnections() {
    try {
        const currentDate = new Date()
        players.data = players.data.filter(
            //expired time less than 5 minutes
            ({ connectionDate }) => (currentDate - connectionDate) / 60000 < 5
        )
    } catch (e) {
        console.log(e)
    }
}
