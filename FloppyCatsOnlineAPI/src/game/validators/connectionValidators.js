import { Player } from '../data/players.js'

/**
 * Object for make connection
 * @typedef {Object} Connector
 * @property {String} name
 * @property {String} token
 * @property {String} ip
 * @property {Number} port
 */

/**
 * @param {Player} player
 * @returns {Boolean}
 */
export function isValidToConnect(player) {
    const { ip, port } = player
    return ip && port
}

/**
 * @param {Connector} connector
 * @returns {Boolean}
 */
export function isValidToRefresh({ ip, name, token, port }) {
    return ip && port && token
}
