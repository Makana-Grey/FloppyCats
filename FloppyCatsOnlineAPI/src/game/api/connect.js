import { Player } from '../data/players.js'
import Router from 'koa-router'

import { connect, refresh } from '../logic/connectionManager.js'

const router = new Router()

/**
 * @param {Player} player
 * @returns {{name: String; token: String}}
 */
router.post('/connect', (ctx, next) => {
    const key = connect(ctx.request.body)

    if (key) {
        ctx.response.status = 200
        ctx.response.body = key
    } else {
        ctx.response.status = 400
        ctx.response.body = `Can't connect player`
    }

    next()
})

/**
 * Object for refresh connection
 * @typedef {Object} Connector
 * @property {String} token
 * @property {String} ip
 * @property {Number} port
 */
router.post('/refresh', (ctx, next) => {
    if (refresh(ctx.request.body)) {
        ctx.response.status = 200
    } else {
        ctx.response.status = 400
        ctx.response.body = `Can't find player`
    }

    next()
})

export default router.routes()
