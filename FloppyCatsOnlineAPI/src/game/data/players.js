export class Player {
    /** @type {String} */
    name = ''

    /** @type {String} */
    token = ''

    /** @type {String} */
    ip = ''

    /** @type {Number} */
    port = 0

    /** @type {Boolean} */
    isPublic = false

    /** @type {Boolean} */
    isPlay = false

    /** @type {Date | undefined} */
    connectionDate = undefined
}

/** @type {{data: Player[]}} */
export const players = {
    data: [],
}
